# peacks in absolute values of something
function p = myPeaks(x,threshold)
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
