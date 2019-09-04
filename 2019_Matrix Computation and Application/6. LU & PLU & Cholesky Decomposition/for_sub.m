function x = for_sub(L, b)
% Solve linear system using forkward substitution
% Input: Lower Triangular Matrix L
%        Nonhomogenous Terms b
% Output: Solution of the linear system

    [m, m] = size(L);
    x = zeros(m, 1);

    x(1) = b(1) / L(1, 1);
    
    % Execute backward substitution
    for k = 2:m
        
        x(k, 1) = (b(k) - L(k, 1:k-1) * x(1:k-1, 1)) / L(k, k);
        
    end
end