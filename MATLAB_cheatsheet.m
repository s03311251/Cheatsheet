%% Array
A = [1 2 3 4 5] % horizontal
A = [1;2;3;4;5] % vertical

A = [1:5] % [1 2 3 4 5]
A = 0:0.5:2 % [0 0.5000 1.0000 1.5000 2.0000]
A = linspace(1,2,5) % 5 spaces between 1 and 2: [1 1.25 1.5 1.75 2]

A = zeros(2,3) % [0 0 0; 0 0 0]
A = ones(2,3) % [1 1 1; 1 1 1]



%% Transpose
B = A.'
B = transpose(A) % both OK



%% Operations on entries
X(1,1) = 1 % (1,1) is the 1st entry

A = [1 3 5]
B = [2 4 6]

A .* B % [2 12 30]
A ./ B % [0.5 0.75 0.833333333333333]
A .^ B % [1 81 15625]



%% Exponential
exp(1i*pi) % -1.0000 + 0.0000i



%% Matrix calculation
% AX=B, find X
X = inv(A)*B
X = A\B % both OK



%% For Loop
for x = 1:6
    for y = 1:6
        Y(x,y) = 2*x+y^2
    end
end



%% While Loop
i = 0; j = 0; sum = 0;
while i <= 20
    while j <= 5
        sum = sum + i + 2 * j;
        j = j + 1;
    end
    i = i + 1;
end
sum



%% Convolution
conv(u,v)



%% Plot Graph
plot(t,x);
title(‘my first plot’); ylabel(‘x(t)’); xlabel(‘Time(seconds)’);
set(gca,’fontsize’,10);
set(gcf,’color’,’w’);
axis([0 500 –5 5]);
grid on;

% On the same graph
t1 = linspace(-5,5,100);
y = 1+t1.^3;
t2 = linspace(0,10,100);
x = cos(2*pi*t2);
t3 = linspace(2,30,100);
z = (2+1./t3).^2;
t4 = linspace(-100,100,100);
w = 5*t4-8;
plot(t1,y,t2,x,t3,z,t3,w)

% Subplot
