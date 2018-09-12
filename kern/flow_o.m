function kk=flow_o(name)
threshold=30;
dd=30;
n=6;
im=rgb2gray(imread(name));
%m=conv2(ones(1,30),1,im);
%m=abs(diff(m));
m2=abs(conv2(ones(1,30),[1 -1],im,'same'));
m=conv2(m2,hanning(30)','same');
m=uint8(m./max(max(m)).*255);

d=size(m);
m(d(1),:)=0;
%[x,y]=meshgrid(1:d(1),50:100:d(2));
%plot3(x',y',uint16(m(:,50:100:d(2))))
%plot(sum(m,2));

%plot(double(m(:,50:100:d(2)))+y'/10)

%figure;
%hold on
%for n=50:100:d(2),
%    plot(m(:,n)+n);
%end;
%hold off

s=sum(m,2);
xc=xcorr(s);
[pk,ind]=findpeaks(xc,'sortstr','descend');
w=abs(ind(3)-ind(2))/2;
t=zeros(1,n*w+1);
t(1:w:n*w+1)=255;
%xc=xcorr(s,t);
[v,ind]=max(xcorr(s,t));
df=ind-length(s);
%plot(ind);
%[v,ind]=max(m(df-15:df+15,:));
l=df:w:n*w+df+1;
    
l=reshape(repmat(l,2*dd+1,1)+repmat((-dd:dd)',1,length(l)),1,length(l)*(2*dd+1));
mm=uint8(zeros(size(m)));
mm(l,:)=uint8(m(l,:));
imshow(mm);
%imshow(mm>threshold);
%[x,y]=meshgrid(1:d(1),50:100:d(2));
%plot3(x',y',uint16(mm(:,50:100:d(2))));

pp=zeros(n+1,d(2));
k=zeros(n+1,3);
for i=1:n+1
    %[v,pp(i,:)]=max(m(df+(i-1)*w-dd:df+(i-1)*w+dd,:));
    pp(i,:)=double(m(df+(i-1)*w-dd:df+(i-1)*w+dd,:))'*(df+(i-1)*w-dd:df+(i-1)*w+dd)'./sum(double(m(df+(i-1)*w-dd:df+(i-1)*w+dd,:)),1)';
    k(i,:)=polyfit(200:d(2)-200,pp(i,200:d(2)-200),2);
end;
%figure,plot(pp')
%for i=1:n+1
%    ll=uint16(polyval(k(i,:),1:d(2)));
%    for j=1:d(2),
%        im(ll(j),j)=255;
%    end;
%end;

%p3=polyfit(1:n,k(:,1)',3);
p3=polyfit(df:w:n*w+df+1,k(:,1)',3);
x=meshgrid(1:d(2),1:d(1));

yy=zeros(d);
for i=1:d(1),
k=polyval(p3,i);
kk=[k -k*d(2) k*d(2)*d(2)/4+i];
yy(i,:)=polyval(kk,1:d(2));
end;
im=interp2(im,x,yy);

imshow(im);