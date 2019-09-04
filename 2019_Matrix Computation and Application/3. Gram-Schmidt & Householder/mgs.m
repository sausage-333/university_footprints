function [Q, R] = mgs(A)
% Computes a reduced QR factorization A = Q_hat * R_hat
% using Modified Gram-Schmidt orthogonalization
%
%  Input: Matrix A having EQUAL or MORE ROWS than columns (m x n)
% Output: Decomposed matrix Q having orthornormal column vectors (m x n)
%         Decomposed triangular matrix R (n x n)
%
% Assume that only matrix satisfying input condition is input to this algorithm   

    [m n] = size(A);
    
    V = A;
    Q = zeros(m, n);
    R = zeros(n, n);
    
    for i = 1:n
        R(i, i) = norm(V(:, i));
        Q(:, i) = V(:, i) / R(i, i);
        
        for j = (i+1):n
            R(i, j) = Q(:, i)' * V(:, j);
            disp(R);
            V(:, j) = V(:, j) - R(i, j) * Q(:,i);
        end
    end
end