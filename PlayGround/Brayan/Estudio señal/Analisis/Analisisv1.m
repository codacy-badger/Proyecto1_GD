    clear, clc, close all;
%Lectura de datos
    datos=xlsread('Data analizar.xlsx');
    %datos=xlsread('Motion.xlsx');
    %datos=xlsread('Nomotion.xlsx');
    %datos=xlsread('xd.xlsx');
%Frecuencia de muestreo
    Fs=125;  %Frecuencia de muestreo del acelerometro
%Datos de magnitud
    ax=datos(:,1);
    ay=datos(:,2);
    az=datos(:,3);
    Ts = 1/Fs;                              % Periodo de muestreo
    t = (0:length(ay)-1)*Ts;                % Vector de tiempo
%Ancho de la ventana de promedio
    n=30;
%Reseteo de offset de la integral
    m=100000;
%Vectores de almacenamiento de datos 
    %Promedio
    ax_mv=[];
    ay_mv=[];
    az_mv=[]; 
    %Derivada
     ax_ov=[];
     ay_ov=[];
     az_ov=[];
     axy_ov=[];
    %Velocidad
     vx_v=[];
     vy_v=[];
     vz_v=[];
     %Deteccion
     detectx=[];
     d_azv=[];
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
   %derivada
   dvx_ant=0;
   
 for i=1:length(ax)/n
     %------------INICIALIZACION DE VALORES--------------
     %Suma
        ax_s=0;
        ay_s=0;
        az_s=0;
     %Suma cada n valores
     for j=n*(i-1)+1:i*n
        ax_s=ax_s+ax(j);
        ay_s=ay_s+ay(j);
        az_s=az_s+az(j);
     end    
    %%Promedio
     m_ax=ax_s/n;
     m_ay=ay_s/n;
     m_az=az_s/n;
    %Derivada
    d_ax=(m_ax-m_ax_ant);
    d_ay=(m_ay-m_ay_ant);
    d_az=(m_az-m_az_ant);
    %Integrando señales
    if(i>2)
        %Integral1
        ax_o=Ts/2*d_ax+Ts/2*d_ax_ant+ax_o_ant;  
        ay_o=Ts/2*d_ay+Ts/2*d_ay_ant+ay_o_ant;  
        az_o=Ts/2*d_az+Ts/2*d_az_ant+az_o_ant;  
        %Integral2
        vx=Ts/2*ax_o+Ts/2*ax_o_ant+vx_ant;
        vy=Ts/2*ay_o+Ts/2*ay_o_ant+vy_ant;
        vz=Ts/2*az_o+Ts/2*az_o_ant+vz_ant;
        
        %Derivando vx
        dvx=vx-vx_ant;
        %Condicion de deteccion
        %if dvx>0 && dvx_ant<0
        if dvx>0 && dvx_ant<0 && dvx-dvx_ant>0.001 && abs(d_az)<10
        %if (dvx>0 && dvx_ant<0) && abs(d_az)<10    
            detect=5;
        else
            detect=-5;
        end
        %Actualizando valores
        %if mod(i,m)==0
        if i==m
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
        else
            %Integral1
            ax_o_ant=ax_o;
            ay_o_ant=ay_o;
            az_o_ant=az_o;
            %Integral2
            vx_ant=vx;
            vy_ant=vy;
            vz_ant=vz;
            %Derivada
            dvx_ant=dvx;
        end
        %Vectores
        %Sin offset
        ax_ov=[ax_ov,ax_o];
        ay_ov=[ay_ov,ay_o];
        az_ov=[az_ov,az_o];
%        axy_ov=[axy_ov,axy_o];
        %Velocidad angular
        vx_v=[vx_v,vx];
        vy_v=[vy_v,vy];
        vz_v=[vz_v,vz];
        %Detection
         detectx=[detectx,detect];
         d_azv=[d_azv,dvx];
    end
    %Actualizando valores
        %Media
        m_ax_ant=m_ax;
        m_ay_ant=m_ay;
        m_az_ant=m_az;
        %Derivada
        d_ax_ant=d_ax;
        d_ay_ant=d_ay;
        d_az_ant=d_az;

    %VECTORES
     %Promedio
     ax_mv=[ax_mv,m_ax];
     ay_mv=[ay_mv,m_ay];
     az_mv=[az_mv,m_az];
    

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
    a=1:length(ax_ov);
    plot(a,ax_ov,a,ay_ov,a,az_ov)  
    %plot(a,ax_ov,a,ay_ov)  
    %plot(a,ax_ov)  
    grid on
    title('Señal sin offset');
      figure
    a=1:length(vx_v);
    %plot(a,vx_v,a,vy_v,a,vz_v)  
    %plot(a,10*vx_v,a,ax_ov)  
    plot(a,10*vx_v,a,detectx,a,ay_mv(3:end)/max(ay_mv),a,az_mv(3:end)/max(az_mv))  
    grid on
    title('Velocidades angulares');
    figure
    %as=lsim(tf(1,[1.5 1]),vx_v,a);
    %plot(a,vx_v,a,as)
    plot(a,d_azv,a,detectx/100)        
    %Prueba
    %Magnitud
    A=sqrt(ax_ov.^2+ay_ov.^2+az_ov.^2);
    a=1:length(A);
    plot(a,A,a,ay_ov)
    figure
    dx=diff(ax_mv);
    dy=diff(ay_mv);
    dz=diff(az_mv);
    a=1:length(dx);
    detects=[];
    detectr=[];
    dx_ant=0;
    for i=1:length(dx)
        if dx(i)>0 && dx_ant<0
            if dy(i)>0 && dy_ant<0
            detectx=5;
        else
            detectx=-5;
            end
        else
            detectx=-5;
            
        
        end
      detects=[detects,detectx];
      %detectr=[detectr,detecty];
      dx_ant=dx(i);
      dy_ant=dy(i);
    end
    
    plot(a,detects,a,ax_mv(2:end))
    
