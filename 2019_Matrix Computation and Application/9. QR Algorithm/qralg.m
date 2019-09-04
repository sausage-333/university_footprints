function [Tnew, iter] = qralg(T)
% Executes QR algorithm for Tridiagonal matrix T
% until abs(T(m, m-1)) is lower than 10^-12
%
%  Input: Tridiagonal Matrix T (m x m)
% Output: Matrix Containing Eigenvalue at the last diagonal entries (m x m)
%
% Assume that only matrix satisfying input condition is input to this algorithm   

    [m, m] = size(T);
    
    iter = 0;
    
    while (abs(T(m, m-1)) > 10^-12)
        
        [Q_k, R_k] = qr(T);
        T = R_k * Q_k;
        
        iter = iter + 1;
    end

    Tnew = T;
    
end