function coeff = hermite(numbers, values, derivatives)
% Making Hermite polynomial coefficients using divided-difference
%
% Input
%     numbers: VECTOR with given numbers information
%      values: VECTOR with given values information
%              It must be in the same entry position as the numbers vector
%              It must have the same dimension with numbers vector
% derivatives: VECTOR with given derivatives information
%              It must be in the same entry position as the numbers vector
%              It must have the same dimension with numbers vector
%
% Output
%       coeff: MATRIX containing coefficients of Hermite Polynomial
%  

    format long

    size_mat = size(numbers);
    order = size_mat(1) - 1;

    whole_coeff = zeros(2*order+2, 2*order+2);
    zet = zeros(2*order+2, 1);
    
    for i = 0:order
        zet(2*i + 1, 1) = numbers(i+1, 1);
        zet(2*i + 2, 1) = numbers(i+1, 1);
        whole_coeff(2*i + 1, 1) = values(i+1, 1);
        whole_coeff(2*i + 2, 1) = values(i+1, 1);
        whole_coeff(2*i + 2, 2) = derivatives(i+1, 1);
        
        if i == 0
            continue
        end
        
        whole_coeff(2*i + 1, 2) = (whole_coeff(2*i + 1, 1) - whole_coeff(2*i, 1))...
                           /(zet(2*i + 1, 1) - zet(2*i, 1));
    end

    for i = 2:(2*order+1)
        for j = 2:i
            whole_coeff(i+1, j+1) = (whole_coeff(i+1, j) - whole_coeff(i, j)) ...
                               /(zet(i+1,1) - zet(i-j+1, 1));
            
        end
    end
    
    coeff = zeros(2*order+2, 1);
    
    for i = 1:(2*order+2)
        coeff(i, 1) = whole_coeff(i, i);
    end
    
end
