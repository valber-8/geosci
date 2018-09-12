function m=flow(name)
im=uint16(rgb2gray(imread(name)));
%m=conv2(ones(1,30),1,im);
%m=abs(diff(m));
m=abs(conv2(ones(1,30),[1 -1],im));
m=conv2(1,hanning(30),m);
m=uint8(m./max(max(m)).*255);

%[x,y]=meshgrid(1:d(1),50:100:d(2));
%plot3(x',y',uint16(m(:,50:100:d(2))))
%plot(sum(m,2));
