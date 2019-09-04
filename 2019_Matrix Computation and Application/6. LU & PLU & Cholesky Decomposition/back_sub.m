function x = back_sub(U, b)
% Solve linear system using backward substitution
% Input: Upper Triangular Matrix L
%        Nonhomogenous Terms b
% Output: Solution of the linear system

    [m, m] = size(U);
    x = zeros(m, 1);

    x(m) = b(m) / U(m, m);
    
    % Execute backward substitution
    for k = m-1:-1:1
        
        x(k, 1) = (b(k) - U(k, k:m) * x(k:m, 1)) / U(k, k);
        
    end
end