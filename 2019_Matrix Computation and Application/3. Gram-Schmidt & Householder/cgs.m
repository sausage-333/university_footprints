function [Q, R] = cgs(A)
% Computes a reduced QR factorization A = Q_hat * R_hat
% using Classical Gram-Schmidt orthogonalization
%
%  Input: Matrix A having EQUAL or MORE ROWS than columns (m x n)
% Output: Decomposed matrix Q having orthornormal column vectors (m x n)
%         Decomposed triangular matrix R (n x n)
%
% Assume that only matrix satisfying input condition is input to this algorithm   

    [m n] = size(A);
    
    V = zeros(m, n);
    Q = zeros(m, n);
    R = zeros(n, n);
    
    V(:, 1) = A(:, 1);
    R(1, 1) = norm(V(:, 1));
    Q(:, 1) = V(:, 1) / R(1, 1);
    
    for j = 2:n
        V(:, j) = A(:, j);
        for i = 1:(j-1)
            R(i, j) = Q(:, i)' * A(:, j);
            V(:, j) = V(:, j) - R(i, j) * Q(:, i);
        end
    R(j, j) = norm(V(:, j));
    Q(:, j) = V(:, j) / R(j, j);
    end
end