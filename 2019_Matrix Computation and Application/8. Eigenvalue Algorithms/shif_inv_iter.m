function [lambda, iter] = shifted_inverse_iteration(A, v, mu, tol)
% Calculate the nearest eigenvalue from mu
% Input
%     A: Real and Symmetric Square matrix
%     v: Initial vector which has 2-norm as 1
%    mu: Amount of shifting
%   tol: Tolerance with pre_lambda and newly obtained lambda 
% Output
%lambda: Estimated eigenvalue
%  iter: Number of Iteration

tic

format long

    [m, m] = size(A);
    
    % 1st iteration
    w = (A - mu * eye(m)) \ v;
    v = w / norm(w);
    lambda = transpose(v) * A * v;

    % 2nd iteration
    w = (A - mu * eye(m)) \ v;
    v = w / norm(w);
    pre_lamda = lambda;
    lambda = transpose(v) * A * v;
    
    iter = 2;
    
    % 3rd Iteration
    while (abs(lambda - pre_lamda) >= tol)
       
        w = (A - mu * eye(m)) \ v;
        v = w / norm(w);
        pre_lamda = lambda;
        lambda = transpose(v) * A * v;
        
        iter = iter + 1;
        
    end

 toc
    
end