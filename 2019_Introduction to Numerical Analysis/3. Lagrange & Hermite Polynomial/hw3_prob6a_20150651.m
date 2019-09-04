function coeff = lagrange(numbers, values)
% Making Lagrange polynomial coefficients using divided-difference
%
% Input
% numbers: VECTOR with given numbers information
%  values: VECTOR with given values information
%          It must be in the same entry position as the numbers vector
%          It must have the same dimension with numbers vector
%
% Output
%   coeff: VECTOR containing coefficients of Lagrange Polynomial
%          coeff(m, 1) corresponds to F_(m-1),(m-1)

    format long

    size_mat = size(numbers);
    order = size_mat(1) - 1;

    whole_coeff = zeros(order+1, order+1);

    for i = 1:(order+1)
        whole_coeff(i, 1) = values(i, 1);
    end

    for i = 2:(order+1)
        for j = i:(order+1)
            whole_coeff(j, i) = (whole_coeff(j, i-1) - whole_coeff(j-1, i-1)) ...
                               /(numbers(j,1) - numbers(j-i+1, 1));
        end
    end
    
    coeff = zeros(order+1, 1);
    
    for i = 1:(order+1)
        coeff(i, 1) = whole_coeff(i, i);
    end
        
end