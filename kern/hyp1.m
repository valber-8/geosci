# hypothesis 1
# now I got the best result with band = 30, threshold = 26
function im_out=hyp1(name, band, threshold)
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
		p = myPeaks(x,threshold);
		p = p.*255;
		for j=1:1:band
			im_out(:,column+j-1)=p';
		end
		column = i+band;
	end
#	imwrite (im_out,strcat(name,".b",int2str(band),".th",int2str(threshold),".out.jpg"),'jpg');
imshow(im_out);
endfunction
