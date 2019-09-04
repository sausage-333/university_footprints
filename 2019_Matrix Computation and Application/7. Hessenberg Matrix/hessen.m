function [H] = hessen(A)
% Computes a Hessenberg matrix H using Householder reflections
% For Hermitian Matrix, Hessenberg matrix is Tridiagonal
%
%  Input: Square Matrix A (m x m)
% Output: Hessenberg matrix H (m x M)
%
% Assume that only matrix satisfying input condition is input to this algorithm   
   
    [m, m] = size(A);
    
    for k = 1:(m-2)
        x = A((k+1):m, k);
    
        % Householder Algorithm for obtaining Hessenberg matrix
        if (x(1)>=0)
            sign = 1;
        else
            sign = -1;
        end
        
        v_k = sign * norm(x) * eye(m-k, 1) + x;
        v_k = v_k / norm(v_k);
        
        A((k+1):m, k:m) = A((k+1):m, k:m) - 2 * v_k * (v_k' * A((k+1):m, k:m));
        A(1:m, (k+1):m) = A(1:m, (k+1):m) - 2 * (A(1:m, (k+1):m) * v_k) * v_k';
    
        % Prints all the steps
        A
    end    
    
    H = A;
    
end