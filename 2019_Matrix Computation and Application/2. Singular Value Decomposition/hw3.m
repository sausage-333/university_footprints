sigma = svd(Check);

[U S V] = svd(Check);

Check_approx = S(1,1) * U(:,1) * (V(:,1))' ...
               + S(2,2) * U(:,2) * (V(:,2))' ...
               + S(3,3) * U(:,3) * (V(:,3))';
           
imshow(Check_approx);