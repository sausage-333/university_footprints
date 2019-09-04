% hw8_prob1_20150651.m
clear all;

load('A_D_b.mat');
n = size(A,1);

x = zeros(n, 1);
for i=1:n
    x(i) = 1;
end

for epsilon = [10^(-2) 10^(-4)]
    
    iter = 1;
    
    while (i <= n)
        if (x(i) == norm(x, inf))
            p = i;
            break
        end 
        i = i + 1;
    end

    x = x / x(p);
    
    while (iter <= 200)
       
        y = A * x;
        mu = y(p);
        
        while (i <= n)
            if (y(i) == norm(y, inf))
                p = i;
                break
            end 
            i = i + 1;
        end
        
        if (y(p) == 0)
           
            fprintf('A has the eigenvalue 0 selecct a new vector x and restart please.\n')'
            break
            
        end
        
        err = norm(x - y / y(p), inf) / norm(y / y(p), inf);
        x = y / y(p);
        
        if (err < epsilon)
            break
        end
        
        iter = iter + 1;
        
    end
    
    error = norm(A*x - mu*x, inf);
    
    disp('-------------------------------')
    disp(sprintf('Power method w/ epsilon = %0.5g', epsilon))
    disp('-------------------------------')
    disp(sprintf('# of iterations: %d', iter))
    disp(sprintf('eigenvalue approximation (mu): %0.5g', mu))
    disp(sprintf('||A*x - mu*x||: %0.5g', error))
end