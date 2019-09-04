%%% Set given matrix A
%%% sqrt stands for expressing root, i stands for imaginary number 
A = [0                         1/sqrt(3) + 1i/sqrt(3)    1/sqrt(6) - 1i/sqrt(6);
     1/sqrt(6) + 1i/sqrt(3)    -1i/sqrt(6)               1/sqrt(3);
     1/sqrt(3) - 1i/sqrt(6)    1/sqrt(6)                 1i/sqrt(3);];

%%% (a)
%%% inv calculates inverse matrix
A_1 = inv(A)

%%% (b)
%%% ctranspose for Hermitian matrix
A_2 = ctranspose(A);

%%% mtimes calculates matrix multiplication
B = mtimes(A, A_2)

C = mtimes(A_2, A)