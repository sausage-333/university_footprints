function [e_w] = wilkinson_eig(A)

    [m, m] = size(A);
    e_w = zeros(m, 1);
    
    T = tridiag(A);
    
    sub_entry = zeros(m^3, 1);
    iter = 1;
    sub_entry(iter, 1) = abs(T(m, m-1));
    
    while (m > 1) 
        
        while (abs(T(m, m-1)) > 10^-12)

            a_m1 = T(m-1, m-1);
            b_m1 = T(m-1, m);
            a_m = T(m, m);
            del = (a_m1 - a_m) / 2; 
          
            if (del >= 0)
                sgn = 1;
            else
                sgn = -1;
            end
            
            mu = a_m - sgn * b_m1^2 / (abs(del) + sqrt(del^2 + b_m1^2));
            
            [Q_k, R_k] = qr(T - mu * eye(m));
            T = R_k * Q_k + mu * eye(m);

            iter = iter + 1;
            sub_entry(iter, 1) = abs(T(m, m-1));

        end
        
        e_w(m, 1) = T(m, m);
        
        m = m - 1;
        T = T(1:m, 1:m);

    end

    e_w(1, 1) = T(1, 1);
    
    semilogy(sub_entry);
    
end

function [Tnew] = qralg(T)

    [m, m] = size(T);
    
    while (abs(T(m, m-1)) > 10^-12)
        
        [Q_k, R_k] = qr(T);
        T = R_k * Q_k; 
    end

    Tnew = T;
    
end

function [T] = tridiag(A)
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
    
    end    
    
    T = A;
    
end