close all;
clear;
x=1:0.1:10000;
y=3*sin(2*pi*0.03*x);
n=0.5*(rand(1,length(x))-0.5);
r=y+n;
e=Adaptivefilter(r,n,0.01,30);
plot(x,y,x,e);
