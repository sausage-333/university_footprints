function [lambda, iter] = rayleigh_quotient_iteration(A, v, tol)
% Calculate the eigenvalue rapidly
% Input
%     A: Real and Symmetric Square matrix
%     v: Initial vector which has 2-norm as 1
%   tol: Tolerance with pre_lambda and newly obtained lambda 
% Output
%lambda: Estimated eigenvalue
%  iter: Number of Iteration

tic

    [m, m] = size(A);

    % Initial lambda
    lambda =  transpose(v) * A * v;
    
    % 1st iteration
    w = (A - lambda * eye(m)) \ v;
    v = w / norm(w);
    lambda = transpose(v) * A * v;
    
    % 2nd iteration
    w = (A - lambda * eye(m)) \ v;
    v = w / norm(w);
    pre_lamda = lambda;
    lambda = transpose(v) * A * v;
    
    iter = 2;
    
    % 3rd Iteration
    while (abs(lambda - pre_lamda) >= tol)
       
        w = (A - lambda * eye(m)) \ v;
        v = w / norm(w);
        pre_lamda = lambda;
        lambda = transpose(v) * A * v;
        
        iter = iter + 1;
        
    end

 toc
    
end