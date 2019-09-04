function [L] = chol_dcmp(A)
% Obtain Cholesky decomposition of positive definite hermitian matrix A
% A = R'R
% Input: mxm positive definite hermitian matrix A
% Output: Upper Triangular Matrix R

    [m, m] = size(A);

    R = A;

    % Execute Cholesky Factorization
    for k = 1:m
        R(k, k:m) = R(k, k:m) / sqrt(R(k, k));
        
        % Make lower than diagonal entries 0
        % to obtain Upper Triangular Matrix
        if k+1 <= m
            R(k+1:m, k) = 0;
        end
        
        for j = (k+1):m
            R(j, j:m) = R(j, j:m) - R(k, j:m) * R(k, j)';
        end
        
    end
    
    L = R';
    
end