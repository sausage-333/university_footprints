format long

m = 1000;
Z = randn(m, m);

A = Z' * Z;
b = randn(m, 1);

tic

% A = R'R
[R] = chol_dcmp(A);

% R'y = b // Forward Substitution 
y = for_sub(R', b);

% Rx = y // Backward Substitution
x = back_sub(U, y);

toc

function x = for_sub(L, b)
% Solve linear system using forward substitution
% Input: Lower Triangular Matrix L
%        Nonhomogenous Terms b
% Output: Solution of the linear system x

    [m, m] = size(L);
    x = zeros(m, 1);

    x(1) = b(1) / L(1, 1);
    
    % Execute backward substitution
    for k = 2:m
        
        x(k, 1) = (b(k) - L(k, 1:k-1) * x(1:k-1, 1)) / L(k, k);
        
    end
end

function x = back_sub(U, b)
% Solve linear system using backward substitution
% Input: Upper Triangular Matrix R
%        Nonhomogenous Terms b
% Output: Solution of the linear system x

    [m, m] = size(U);
    x = zeros(m, 1);

    x(m) = b(m) / U(m, m);
    
    % Execute backward substitution
    for k = m-1:-1:1
        
        x(k, 1) = (b(k) - U(k, k:m) * x(k:m, 1)) / U(k, k);
        
    end
end

function [L, U] = lu_dcmp(A)
% Obtain LU decomposition of square matrix A
% P = LU
% Input: mxm square matrix A
% Output: Upper Triangular Matrix L, Lowe Triangular Matrix U

    [m, m] = size(A);

    U = A;
    L = eye(m);

    % Execute Gauss Elimination
    for k = 1:(m-1)
        for j = (k+1):m
            L(j, k) = U(j, k) / U(k, k);
            U(j, k:m) = U(j, k:m) - L(j, k) * U(k, k:m);
        end
    end
end

function [R] = chol_dcmp(A)
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
end