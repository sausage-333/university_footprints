% Set hello matrix first
% Use spy method to display matrix visually
spy(hello);

% svd method returns singular values
sigma = svd(hello);

% Plot singular values in linear scale
%figure(1);
%plot(sigma);
%title('Singular values in linear scale');

% Plot singular values in log scale
%figure(2);
%semilogy(sigma);
%title('Singular values in log scale');

% Construct rank-i matrix B
[U S V] = svd(hello);

% rank 4
B = S(1,1) * U(:,1) * (V(:,1))' ...
    + S(2,2) * U(:,2) * (V(:,2))' ...
    + S(3,3) * U(:,3) * (V(:,3))' ...
    + S(4,4) * U(:,4) * (V(:,4))' ...
    + S(5,5) * U(:,5) * (V(:,5))'...
    + S(6,6) * U(:,6) * (V(:,6))'...
    + S(7,7) * U(:,7) * (V(:,7))'...
    + S(8,8) * U(:,8) * (V(:,8))'...
    + S(9,9) * U(:,9) * (V(:,9))'...
    + S(10,10) * U(:,10) * (V(:,10))';

pcolor(B);
colormap(gray);
% Make axis with matrix index
axis ij