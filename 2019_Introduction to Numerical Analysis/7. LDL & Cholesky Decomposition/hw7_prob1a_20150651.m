function [L, D] = ldlt_dcmp(A)
% Obtain LDL' decomposition of positive definite hermitian matrix A
% A = LDL'
% Input: mxm positive definite hermitian matrix A
% Output: Lower Triangular Matrix L, Diagonal Matrix D

    [m, m] = size(A);

    v = zeros(m, 1);
    L = eye(m, m);
    D = zeros(m, m);
    
    for i = 1:m
    
        for j = 1:(i-1)            
            v(j) = L(i, j) * D(j, j);
        end
        
        sum1 = 0;
        for j = 1:(i-1)
            sum1 = sum1 + L(i, j) * v(j);
        end
            
        D(i, i) = A(i, i) - sum1;
        
        for j = (i+1):m
            
            sum2 = 0;
            for k = 1:(i-1)
                sum2 = sum2 + L(j, k) * v(k);
            end
            
            L(j, i) = (A(j, i) - sum2) / D(i, i); 
        
        end
    
    end
        
end