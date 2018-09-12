function [f,y]=fft_curve(x)
L=length(x);
NFFT = 2^nextpow2(L); % Next power of 2 from length of y
y = fft(x,NFFT)/L;
f = 1/2*linspace(0,1,NFFT/2+1);

y=2*abs(y(1:NFFT/2+1)); 