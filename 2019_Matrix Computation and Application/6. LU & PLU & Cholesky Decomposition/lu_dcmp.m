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