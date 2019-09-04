% hw8_prob2_StudentNumber.m
clear all;

load('A_D_b.mat');
n = size(A,1);

epsilon = 10^(-10);

invD = inv(D);

% Jacobi
x = zeros(n, 1);
xo = zeros(n, 1);

iter = 1;

while (iter <= 200)
    
    x = invD * (D - A) * xo + invD * b; 
    
    if (norm(x - xo) / norm(x) < epsilon)
        break
    end
    
    iter = iter + 1;
    xo = x;
    
end    

err = norm(A * x - b);

disp('-------------------------------')
disp('Jacobi method')
disp('-------------------------------')
disp(sprintf('# of iterations: %d', iter))
disp(sprintf('||A*x - b||: %0.5g', err))
figure(1);
imagesc(reshape(x, [100 100])), colormap(gray), colorbar;
title(sprintf('Jacobi method after %d iterations', iter));

% Conjugate gradient
x = zeros(n,1);

r = b - A * x;
v = r;

iter = 1;

while (iter <= 200)
    
    xo = x;
    
    t = r.' * r / (v.' * A*v);
    x = x + t*v;
    
    if (norm(x - xo) / norm(x) < epsilon)
        break
    end
    
    ro = r;
    r = r - t *A*v;
    s = r.' * r / (ro.' * ro);
    v = r + s*v;
    
    iter = iter + 1;
    
end

err = norm(A * x - b);

disp('-------------------------------')
disp('Conjugate gradient method')
disp('-------------------------------')
disp(sprintf('# of iterations: %d', iter))
disp(sprintf('||A*x - b||: %0.5g', err))
figure(2);
imagesc(reshape(x, [100 100])), colormap(gray), colorbar;
title(sprintf('Conjugate gradient method after %d iterations', iter));


