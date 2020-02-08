%1、由模拟滤波器指标（Omegap、Omegas、Rp、As）计算巴特沃斯滤波器指标（阶数 N 和 3dB 截止频率Omegac）
%buttord可用于计算低通、高通、带通、带阻巴特沃斯滤波器指标
%Rp，As分别为通带最大衰减和组带最小衰减（dB），'s'表示模拟滤波器
%根据指标，求得符合指标的、滤波器应有的阶数和截止频率
clc;clear;
Td=1;Fs=1/Td;
Wp=0.2*2*pi;Ws=0.3*2*pi;
Rp=1;
As=15;
Omegap=2/Td*tan(Wp/2);
Omegas=2/Td*tan(Ws/2);
[N,Omegac]=buttord(Omegap,Omegas,Rp,As,'s');
%2、计算连续系统系数a,b0
%归一化（模板巴特沃斯的截止频率Omegac=1）的模拟滤波器，零点、极点、增益
%级联式，z0,p0,k0分别为零点、极点、增益
%去归一化（求出真正滤波器的Omegac）,得到级联式
%级联式转换为一般式（由根求系数）：为由一般式为跳板，计算并联式
[z0,p0,k0]=buttap(N);
[Bap,Aap]=zp2tf(z0,p0,k0); 
[b,a]=lp2lp(Bap,Aap,Omegac);
[bz,az]=bilinear(b,a,Fs); 
[H,W]=freqs(bz,az);
figure(1);
plot(W/pi,20*log10(abs(H))); 
title('巴特沃斯滤波器')
xlabel('频率');
ylabel('增益(dB)');

f1=10;%第一个点频信号分量频率
f2=30;%第二个点频信号分量频率
f3=45;%第三个点频信号分量频率
fs=100;%采样率
T=2;%间隔长度
n=round(T*fs);%采样点个数
t=linspace(0,T,n);
y=cos(2*pi*f1*t)+cos(2*pi*f2*t)+cos(2*pi*f3*t)+randn(size(t));
figure(2);
subplot(2,1,1);
plot(t,y);
title('输入信号时域图像');
xlabel('t/s');
ylabel('V');
fft_y=fftshift(fft(y));
f=linspace(-fs/2,fs/2,n);
subplot(2,1,2);
plot(f,abs(fft_y));
title('输入信号频域图像');
xlabel('f/Hz');
ylabel('V');
axis([ 0 50 0 100]);

%test my filter
x1=[0,0,0,0,0];
y1=[0,0,0,0,0];
final2=[];
for i=1:n
    for j=1:N
        x1(j) = x1(j+1);
    end
    x1(N+1) = y(i);
    if (x1(1)==0)
        yn = y(i);
    else
        yn = bz(1) * x1(N+1);
        for k=2:N+1
            yn = yn + bz(k)* x1(N+2-k) - az(k) * y(N+2-k);
        end
    end
    for j2=1:N
        y1(j2) = y1(j2+1);
    end
    y1(N+1) = yn;
    final2 = [final2, yn];
end

figure(3);
final=filter(bz, az, y);
final1=filtfilt(bz,az,y);
subplot(2,1,1);
plot(t,y, t,final, 'b', t,final2, '-r');  
title( '滤波后信号波形时域波形' );
xlabel('t/s');
ylabel('V');

finall=fftshift(fft(final));
subplot(2,1,2);
plot(f,abs(finall));
title( '滤波后信号频域波形' );
axis([ 0 50 0 100]);

