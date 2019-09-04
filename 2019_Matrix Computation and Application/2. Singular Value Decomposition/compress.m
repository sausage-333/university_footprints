
% Read the picture of the tiger, and convert to black and white.
%tiger = rgb2gray(imread('tiger.jpg'));
tiger = rgb2gray(imread('kaist.jpg'));
tiger = im2double(tiger);
% 
% Compute SVD of this tiger
[U, S, V] = svd(tiger);

% Plot the magnitude of the singular values (log scale)
sigmas = diag(S);
figure; plot(log10(sigmas)); title('Singular Values (Log10 Scale)');
figure; plot(cumsum(sigmas) / sum(sigmas)); title('Cumulative Percent of Total Sigmas');

% Show full-rank tiger
%figure; subplot(4, 2, 1), imshow(tiger), title('Full-Rank Tiger');
figure; subplot(2, 2, 1), imshow(tiger), title('Full-Rank KAIST');

% Compute low-rank approximations of the tiger, and show them
%ranks = [400,200,100,50,20,10,5];
ranks = [100, 50, 100];
for i = 1:length(ranks)
    % Keep largest singular values, and nullify others.
    approx_sigmas = sigmas; approx_sigmas(ranks(i)+1:end) = 0;

    % Form the singular value matrix, padded as necessary
    ns = length(sigmas);
    approx_S = S; approx_S(1:ns, 1:ns) = diag(approx_sigmas);

    % Compute low-rank approximation by multiplying out component matrices.
    approx_tiger = U * approx_S * V';

    % Plot approximation
    %subplot(4, 2, i + 1), imshow(approx_tiger), title(sprintf('Rank %d Tiger', ranks(i)));
    subplot(2, 2, i + 1), imshow(approx_tiger), title(sprintf('Rank %d KAIST', ranks(i)));
end

