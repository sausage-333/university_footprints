function [P, L, U] = plu_dcmp(A)
% Obtain PLU decomposition of square matrix A
% PA = LU
% Input: mxm square matrix A
% Output: Pivot Matrix P, Upper Triangular Matrix L, Lowe Triangular Matrix U

    [m, m] = size(A);

    U = A;
    L = eye(m);
    P = eye(m);

    for k = 1:(m-1)
        
        % Find index of Maximum entry from U
        [val, i] = max(abs(U(k:m, k)));
        i = i + k - 1;
        
        % Interchange only occurs when it is needed
        if i ~= k
            
            % Interchange two row vector of U
            temp = U(k, k:m);
            U(k, k:m) = U(i, k:m);
            U(i, k:m) = temp;

            % Interchange two row vector of L
            temp = L(k, 1:k-1);
            L(k, 1:k-1) = L(i, 1:k-1);
            L(i, 1:k-1) = temp;

            % Interchange two row vector of P
            temp = P(k, :);
            P(k, :) = P(i, :);
            P(i, :) = temp;
            
        end
        
        % Execute Gauss Elimination
        for j = (k+1):m
            L(j, k) = U(j, k) / U(k, k);
            U(j, k:m) = U(j, k:m) - L(j, k) * U(k, k:m);
        end
    end
end