    clear, clc, close all;
%Lectura de datos
    %datos=xlsread('Data analizar2.xlsx');
    datos=xlsread('Motion.xlsx');
    %datos=xlsread('Nomotion.xlsx');
%Frecuencia de muestreo
    Fs=125;  %Frecuencia de muestreo del acelerometro
%Datos de magnitud
    ax=datos(:,1);
    ay=datos(:,2);
    az=datos(:,3);
    Ts = 1/Fs;                              % Periodo de muestreo
    t = (0:length(ay)-1)*Ts;                % Vector de tiempo
%Ancho de la ventana de promedio
    n=10;
%Reseteo de offset de la integral
    m=1000;
%Vectores de almacenamiento de datos 
    %Promedio
     ax_mv=[];
     ay_mv=[];
     az_mv=[]; 
    %Velocidad
     vx_v=[];
     vy_v=[];
     vz_v=[];
    %Detection
     detectx_v=[];
     detecty_v=[];
%Valores anteriores
   %Media 
    m_ax_ant=0;
    m_ay_ant=0;
    m_az_ant=0;
   %derivada
    d_ax_ant=0;
    d_ay_ant=0;
    d_az_ant=0;
   %Integral1
    ax_o_ant=0;
    ay_o_ant=0;
    az_o_ant=0;
   %Integral2
    vx_ant=0;
    vy_ant=0;
    vz_ant=0;
   %Derivada
    dvx_ant=0;
   
 for i=1:length(ax)/n
     %------------INICIALIZACION DE VALORES--------------
     %PRIMERA MITAD
     %Suma
        ax_s=0;
        ay_s=0;
        az_s=0;
     for j=n*(i-1)+1:i*n
        ax_s=ax_s+ax(j);
        ay_s=ay_s+ay(j);
        az_s=az_s+az(j);
     end    
    %%Promedio
     m_ax=ax_s/n;
     m_ay=ay_s/n;
     m_az=az_s/n;
    %Integrando señales
     vx=Ts/2*m_ax+Ts/2*m_ax_ant+vx_ant;
     vy=Ts/2*m_ay+Ts/2*m_ay_ant+vy_ant;
     vz=Ts/2*m_az+Ts/2*m_az_ant+vz_ant;
    %Derivando vx
    dvx=vx-vx_ant;
    %Derivando vy
    dvy=vy-vy_ant;
    %Condicion de deteccion
    if dvx>0 && dvx_ant<0
        detectx=-300;
    else
        detectx=0;
    end
    %Actualizando valores
    %Media
    m_ax_ant=m_ax;
    m_ay_ant=m_ay;
    m_az_ant=m_az;
    %Integral2
    vx_ant=vx;
    vy_ant=vy;
    vz_ant=vz;
    %Derivada
    dvx_ant=dvx;
    dvy_ant=dvy;

    %VECTORES
     %Promedio
     ax_mv=[ax_mv,m_ax];
     ay_mv=[ay_mv,m_ay];
     az_mv=[az_mv,m_az];
    %Velocidad angular
     vx_v=[vx_v,vx];
     vy_v=[vy_v,vy];
     vz_v=[vz_v,vz];
     %detection
     detectx_v=[detectx_v,detectx];
 end
%Grafico de la señal en el tiempo
    figure
  % subplot(2,1,1) 
    b=1:length(ax);
    plot(b,ax,b,ay,b,az)    
    grid on
    title('Señal original');
    xlabel('t')
    ylabel('Amplitud en Codigo')
    figure
    a=1:length(ay_mv);
    plot(a,ax_mv,a,ay_mv,a,az_mv)  
    grid on
    title('Señal promedio');
      figure
    a=1:length(vx_v);
    %plot(a,ay_mv,a,vx_v)
    plot(a,vx_v)
    hold on
    stem(a,detectx_v)
    grid on
    title('Velocidades angulares');
    figure
    plot(diff(vy_v))
  
