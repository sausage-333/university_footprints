function [lambda, iter] = power_iteration(A, v, tol)
% Calculate the largest eigenvalue
% Input
%     A: Real and Symmetric Square matrix
%     v: Initial vector which has 2-norm as 1  
%   tol: Tolerance
% Output
%lambda: Estimated eigenvalue
%  iter: Number of Iteration

tic

format long

    % 1st iteration
    w = A * v;
    v = w / norm(w);
    lambda = transpose(v) * A * v;
    
    % 2nd iteration
    w = A * v;
    v = w / norm(w);
    pre_lamda = lambda;
    lambda = transpose(v) * A * v;
    
    iter = 2;
    
    % 3rd Iteration
    while (abs(lambda - pre_lamda) >= tol)
       
        w = A * v;
        v = w / norm(w);
        pre_lamda = lambda;
        lambda = transpose(v) * A * v;
        
        iter = iter + 1;
        
    end

toc
    
end