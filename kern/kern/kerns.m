# peacks in absolute values of something
function p = myPeacks(x,threshold)
	m = max(x);
	thr = m*threshold/100;
	up = 0;
	mx=1;
	for i=1:1:length(x)
		p(i)=0;
		if (up==0)&&(x(i)>=thr)
				up = 1;
				mx = i;
		endif
		if (up==1)&&(x(i)<thr)
			up = 0;
			p(mx)=1;
		endif
		if (up==1)&&(x(i)>x(mx))
				mx=i;
		endif
	end
endfunction

# hypothesis 1
# now I got the best result with band = 30, threshold = 26
function hyp1(name, band, threshold)
	im_in = uint8(imread(name));
	[h,w] = size(im_in);
	im_out = zeros(h,w);
	column=1;
	for i=1:band:w-band
		b = im_in(:,i:i+band);
		for j=1:1:h
			x(j) = (sum(b(j,:)))/band;
		end
		x = abs(diff(x));
		x = conv(x,hanning(30));
		x = x(1:h);
		p = myPeacks(x,threshold);
		p = p.*255;
		for j=1:1:band
			im_out(:,column+j-1)=p';
		end
		column = i+band;
	end
	imwrite (im_out,strcat(name,".b",int2str(band),".th",int2str(threshold),".out.jpg"),'jpg');
endfunction

# user clicks in several places, we find the lines near these places
# y = array of y's of clicks
function clicklines(name,y)
	im_in = uint8(imread(name));
	im_out=im_in./3+170;

	[h,w] = size(im_in);
	v_band = round(w*0.01);
	h_band = round((y(length(y))-y(1))*0.035);
	
	for line=1:1:length(y)
		lup = max(y(line)-h_band,1);
		ldown = min(y(line)+h_band,h);

		mnk_i=1;
		mnk_x=0;
		mnk_y1=0;
		mnk_y2=0;
		column=1;
		for i=1:v_band:w-v_band
			b = im_in(lup:ldown,i:i+v_band);
			x=0;
			for j=1:1:(ldown-lup)
				x(j) = sum(b(j,:));
			end
			x = conv(abs(diff(x)),hanning(30));
			x = x(15:length(x)-15);

			[pval,pnum] = max(x);
			
			# paint	lines
			#for j=1:1:v_band
			#	im_out(lup,column+j)=0;
			#	im_out(lup+1,column+j)=0;
			#	im_out(lup+2,column+j)=255;
			#	im_out(lup+3,column+j)=255;
			#	im_out(ldown-3,column+j)=255;
			#	im_out(ldown-2,column+j)=255;
			#	im_out(ldown-1,column+j)=0;
			#	im_out(ldown,column+j)=0;
			#end

			mnk_x(mnk_i)=i;
			mnk_y1(mnk_i)=pnum;
			mnk_i = mnk_i+1;
			column = i+v_band;
		end

		lend = round(length(mnk_x)*0.1);
		mnk_kf = polyfit(mnk_x(lend:length(mnk_x)-lend),mnk_y1(lend:length(mnk_y1)-lend),2);
		mnk_y2 = mnk_kf(1)*(mnk_x.*mnk_x) .+ mnk_kf(2)*mnk_x .+ mnk_kf(3);
		mnk_y2 = round(mnk_y2);

		# painting
		column=1;
		for i=1:1:length(mnk_y2)
			for j=1:1:v_band
				im_out(lup+mnk_y2(i),column+j)=0;
				im_out(lup+mnk_y2(i)-1,column+j)=0;
				im_out(lup+mnk_y2(i)+1,column+j)=0;
				im_out(lup+mnk_y2(i)-2,column+j)=0;
				im_out(lup+mnk_y2(i)+2,column+j)=0;
				im_out(lup+mnk_y2(i)-3,column+j)=0;
				im_out(lup+mnk_y2(i)+3,column+j)=0;
			end
			column = column+v_band;
		end
	end
	imwrite (im_out,strcat(name,".out.jpg"),'jpg');
endfunction

function clicklines_test1()
	# thank you, Gimp!
	clicklines("data/test.jpg",[15,303,588,873,1146,1425,1722]);
endfunction

function clicklines_test2()
	# thank you, Gimp!
	clicklines("data/inp_1.jpg",[42,270,573,816,1113,1392,1668]);
endfunction

function clicklines_test04()
	# thank you, Gimp!
	clicklines("data/test04.jpg",[292,592,898,1200,1500,1800,2080]);
endfunction

function clicklines_test05()
	# thank you, Gimp!
	clicklines("data/test05.jpg",[420,820,1240,1616,2008]);
endfunction

function clicklines_test06()
	# thank you, Gimp!
	clicklines("data/test06.jpg",[276,560,860,1164,1444,1736,2032]);
endfunction

function clicklines_test06_1()
	# thank you, Gimp!
	y2 = [276,2032];
	wid = (y2(2)-y2(1))/6;
	y6 = y2(1):wid:y2(2);
	y6 = round(y6);
	clicklines("data/test06.jpg",y6);
endfunction
