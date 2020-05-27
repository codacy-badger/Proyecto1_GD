clear, clc, close all;
%Lectura de datos
    datos=xlsread('Datos reales.xlsx');
%Frecuencia de muestreo
    Fs=1;        %Frecuencia de muestreo del acelerometro
    Ts=1/Fs;     %Periodo de muestreo
%Datos de magnitud
    ang=datos(20:100,1);
    T = 1/Fs;                              % Periodo de muestreo
    t = (0:length(ang)-1)*T;                % Vector de tiempo
%Analisis FFT
    NFFT = 2^nextpow2(length(ang));        
    Y = fft(ang,NFFT)/length(ang);
    f = Fs/2*linspace(0,1,NFFT/2+1);
%Calculo de las señales de velocidad y aceleracion
    figure(1)
    v=diff(ang);
    acc=diff(v);
    figure(1)
    plot(ang)
    hold on
    plot(v)
    hold on
    plot(acc)
    hold off
%Grafico de la señal en el tiempo
    figure(2)
    subplot(2,1,1)
    plot(t,ang)    
    grid on
    title('Señal original');
    xlabel('t')
    ylabel('Amplitud en Codigo')
% Grafido del espectro de la señal
    subplot(2,1,2)
    plot(f,2*abs(Y(1:NFFT/2+1))) 
    grid on
    title('Amplitude del espectro')
    xlabel('Frecuencia(Hz)')
    ylabel('|a(f)|')
%-------------EMPEZAMOS EL ANALISIS DE LA SEÑAL----------------    
%Integracion por runge Kutta
vel=[0 0 0 0 0 0 0];        %Condiciones iniciales
for i=8:length(acc)
    dV=mean(abs(diff(acc(i-7:i))));
    %day=abs(ay(i))-abs(ay(i-1));
    if dV > 0.05
     vel=[vel, Ts/2*acc(i)+Ts/2*acc(i-1)+vel(i-1)];
    %vel=[vel,1];
    else
     vel=[vel,0];
    end
end
    figure
    plot(1:length(vel),vel)
    hold on
    plot(1:length(v),v)
    grid on     
    legend('velocidad integrada','velocidad derivada')
    