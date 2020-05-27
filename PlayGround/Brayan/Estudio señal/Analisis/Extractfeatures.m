    clear, clc, close all;
%Lectura de datos
    datos=xlsread('Data analizar3.xlsx');
%Frecuencia de muestreo
    Fs=125;  %Frecuencia de muestreo del acelerometro
%Datos de magnitud
    ax=datos(:,1)/max(datos(:,1));
    ay=datos(:,2)/max(datos(:,2));
    az=datos(:,3)/max(datos(:,3));
    Ts = 1/Fs;                              % Periodo de muestreo
    t = (0:length(ay)-1)*Ts;                % Vector de tiempo
%Diseño de filtro pasa alto   
    %ax=filter(0.0158,0.9843,ax);
    %ay=filter(0.0158,0.9843,ay);
    %az=filter(0.0158,0.9843,az);
% %Eliminando offset mediante derivacion e integracion
%      ax1=diff(ax);
%      ay1=diff(ay);
%      az1=diff(az);
%      ax2=[0];
%      ay2=[0]; 
%      az2=[0];
%   for i=2:length(ax1)-1
%         ax2=[ax2,Ts/2*ax1(i)+Ts/2*ax1(i-1)+ax2(i-1)];
%         ay2=[ay2,Ts/2*ay1(i)+Ts/2*ay1(i-1)+ay2(i-1)];
%         az2=[az2,Ts/2*az1(i)+Ts/2*az1(i-1)+az2(i-1)];  
%   end
%   ax=ax2;
%   ay=ay2;
%   az=az2;
      t = (0:length(ay)-1)*Ts;                % Vector de tiempo

%Ancho de la ventana
    n=50; 
%Vectores de almacenamiento de datos 
    %Promedio
    ax_mv=[];
    ay_mv=[];
    az_mv=[];
    %Desviacion estandar
    d_xv=[];
    d_yv=[];
    d_zv=[];
    %Covarianza
    cxy_v=[];
    cxz_v=[];
    cyz_v=[];
    yfit=[];
%-------------INICIANDO VALORES ANTERIORES-----------
     %Suma
     ax_s2_ant=0;
     ay_s2_ant=0;
     az_s2_ant=0;
     %Suma cuadrados 
     ax2_2_ant=0;
     ay2_2_ant=0;
     az2_2_ant=0;
     %Covarianza
     xy2_ant=0;
     xz2_ant=0;
     yz2_ant=0;    
     
 for i=1:length(ax)/n
     %d_ay(n*(i-1)+1)=0; 
     %------------INICIALIZACION DE VALORES--------------
     %PRIMERA MITAD
     %Suma
        ax_s1=0;
        ay_s1=0;
        az_s1=0;
     %Suma cuadrados
        ax2_1=0;
        ay2_1=0;
        az2_1=0;
     %Multiplicacion
        xy1=0;
        xz1=0;
        yz1=0;
     %SEGUNDA MITAD
     %Suma
        ax_s2=0;
        ay_s2=0;
        az_s2=0;
     %Suma cuadrados
        ax2_2=0;
        ay2_2=0;
        az2_2=0;
     %Multiplicacion
        xy2=0;
        xz2=0;
        yz2=0;
     for j=n*(i-1)+1:i*n
       if j<=n*(i-1)+n/2    
           %Calculando primera mitad de los valores de la ventana
           %Suma
           ax_s1=ax_s1+ax(j);
           ay_s1=ay_s1+ay(j);
           az_s1=az_s1+az(j);
          %Suma cuadrados 
           ax2_1=ax2_1+ax(j)^2;
           ay2_1=ay2_1+ay(j)^2;
           az2_1=az2_1+az(j)^2;
          %Suma productos
           xy1=xy1+ax(j)*ay(j);
           xz1=xz1+ax(j)*az(j);
           yz1=yz1+ay(j)*az(j);
       else 
           %Calculando segunda mitad de los valores de la ventana
           %Suma
           ax_s2=ax_s2+ax(j);
           ay_s2=ay_s2+ay(j);
           az_s2=az_s2+az(j);
           %Suma cuadrados 
           ax2_2=ax2_2+ax(j)^2;
           ay2_2=ay2_2+ay(j)^2;
           az2_2=az2_2+az(j)^2;
           %Covarianza
           xy2=xy2+ax(j)*ay(j);
           xz2=xz2+ax(j)*az(j);
           yz2=yz2+ay(j)*az(j);
       end
     end   
    %------------------OVERLAP-----------------------
    %Suma
     ax_so=ax_s1+ax_s2_ant;
     ay_so=ay_s1+ay_s2_ant;
     az_so=az_s1+az_s2_ant;
    %Suma cuadrados 
     ax2o=ax2_1+ax2_2_ant;
     ay2o=ay2_1+ay2_2_ant;
     az2o=az2_1+az2_2_ant;
    %Suma productos
     xyo=xy1+xy2_ant;
     xzo=xz1+xz2_ant;
     yzo=yz1+yz2_ant;
     
     %-------------------------ACTUAL-----------------------------
     ax_sa=ax_s1+ax_s2;
     ay_sa=ay_s1+ay_s2;
     az_sa=az_s1+az_s2;
    %Actual
    %Suma cuadrados 
     ax2a=ax2_1+ax2_2;
     ay2a=ay2_1+ay2_2;
     az2a=az2_1+az2_2;
    %Suma productos
     xya=xy1+xy2;
     xza=xz1+xz2;
     yza=yz1+yz2;
     
    %----------------CALCULO DE VALORES OVERLAP-----------------
    %Promedio
     m_axo=ax_so/n;
     m_ayo=ay_so/n;
     m_azo=az_so/n;
    %Desviacion estandar
     d_xo=sqrt(ax2o/n-(m_axo)^2);
     d_yo=sqrt(ay2o/n-(m_ayo)^2);
     d_zo=sqrt(az2o/n-(m_azo)^2);
    %covarianza
     cxyo=((1/n)*xyo-m_axo*m_ayo)/(d_xo*d_yo);
     cxzo=((1/n)*xzo-m_axo*m_azo)/(d_xo*d_zo);
     cyzo=((1/n)*yzo-m_ayo*m_azo)/(d_yo*d_zo);
    %---------------CALCULO VALORES ACTUAL-------------------- 
    %%Promedio
     m_axa=ax_sa/n;
     m_aya=ay_sa/n;
     m_aza=az_sa/n;
     %Desviacion estandar
     d_xa=sqrt(ax2a/n-(m_axa)^2);
     d_ya=sqrt(ay2a/n-(m_aya)^2);
     d_za=sqrt(az2a/n-(m_aza)^2);
     %covarianza
     cxya=((1/n)*xya-m_axa*m_aya)/(d_xa*d_ya);
     cxza=((1/n)*xza-m_axa*m_aza)/(d_xa*d_za);
     cyza=((1/n)*yza-m_aya*m_aza)/(d_ya*d_za);
     
     %Prediction
     %yfit1 = predict(trainedClassifier,[m_axo,m_ayo,m_azo,d_xo,d_yo,d_zo,cxyo,cxzo,cyzo]);
     %yfit2 = predict(trainedClassifier,[m_axa,m_aya,m_aza,d_xa,d_ya,d_za,cxya,cxza,cyza]);

    %VECTORES
     %Promedio
     ax_mv=[ax_mv,m_axo,m_axa];
     ay_mv=[ay_mv,m_ayo,m_aya];
     az_mv=[az_mv,m_azo,m_aza];
     %Covarianza
     cxy_v=[cxy_v,cxyo,cxya];
     cxz_v=[cxz_v,cxzo,cxza];
     cyz_v=[cyz_v,cyzo,cyza];
     %Desviación estandar
     d_xv=[d_xv,d_xo,d_xa];
     d_yv=[d_yv,d_yo,d_ya];
     d_zv=[d_zv,d_zo,d_za];
     %Prediccion
     %yfit=[yfit,yfit1,yfit2];
     
    %Actualizando valores
     %Suma
     ax_s2_ant=ax_s2;
     ay_s2_ant=ay_s2;
     az_s2_ant=az_s2;
     %Suma cuadrados 
     ax2_2_ant=ax2_2;
     ay2_2_ant=ay2_2;
     az2_2_ant=az2_2;
     %Covarianza
     xy2_ant=xy2;
     xz2_ant=xz2;
     yz2_ant=yz2;
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
    datos1=[%Promedio
            ax_mv;
            ay_mv;
            az_mv;
            %Covarianza
            cxy_v];
            %cxz_v;
            %cyz_v;
            %Desviación estandar
            %d_xv;
            %d_yv;
            %d_zv];
     plot(datos1')
     grid on
     legend('ax media','ay media','az media','covarianza xy','covarianza xz','covarianza zy',...
         'Desviacion x','Desviacion y','Desviacion z')
  
%    xlswrite('Clasificacion11',datos1)

