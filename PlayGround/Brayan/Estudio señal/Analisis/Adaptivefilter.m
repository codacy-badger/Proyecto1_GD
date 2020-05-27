function [e] = Adaptivefilter(d,x,mu,Nw)
%UNTITLED3 Summary of this function goes here
%   Detailed explanation goes here
N=length(d);    %Longitud de la señal obtenida
w=zeros(1,Nw);  %VECTOR DE COEFICIENTES DEL FILTRO
y=zeros(1,N);   %FILTER OUTPUT 
e=y;
for m=Nw+1:1:N-1
        sum=0;
    for i=1:1:Nw
        sum=sum+w(i)*x(m-i+1); % FUNCION DEL FILTRO ADAPTATIVO
    end
        y(m)=sum;
        e(m)=d(m)-y(m); %CALCULA LA FUNCION ERROR
    for i=1:1:Nw
        w(i)=w(i)+2*mu*e(m)*x(m-i+1); %ACTUALIZA LOS COEFICIENTES DEL FILTRO
    end
end

end

