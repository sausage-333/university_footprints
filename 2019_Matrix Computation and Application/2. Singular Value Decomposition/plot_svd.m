function plot_svd(A)
% Input  2x2 Matrix A
% Output Plot of right singluar vectors on unit circle
%        and left singular vectors on appropriate ellipse

    % Draw Unit Circle
    t = 0:0.001:2*pi;
    cir_x = cos(t);
    cir_y = sin(t);

    % Draw Ellipse made by A
    ellip = A * [cir_x; cir_y];
    ellip_x = ellip(1,:);
    ellip_y = ellip(2,:);
    
    % Obtain SVD of A
    [U, S, V] = svd(A);
    
    % Right singular vectors
    v1 = V(:,1);
    v2 = V(:,2);
    
    % Scaled left singular vectors
    % (ith singular value) * (ith left singular vectors)
    s1u1 = S(1,1) * U(:,1);
    s2u2 = S(2,2) * U(:,2);
    
    % Plot right singular vectors on unit plane
    figure(1);
    plot(cir_x, cir_y, 'k');
    hold on;
    
    t = 0:0.001:1;
    line_x = v1(1,1) * t;
    line_y = v1(2,1) * t;
    plot(line_x, line_y, 'r');
    hold on;
    
    t = 0:0.001:1;
    line_x = v2(1,1) * t;
    line_y = v2(2,1) * t;
    plot(line_x, line_y, 'b');
    
    % Plot left singular vectors on ellipse
    figure(2);
    plot(ellip_x, ellip_y, 'k');
    hold on;
    
    t = 0:0.001:1;
    line_x = s1u1(1,1) * t;
    line_y = s1u1(2,1) * t;
    plot(line_x, line_y, 'r');
    hold on;
    
    t = 0:0.001:1;
    line_x = s2u2(1,1) * t;
    line_y = s2u2(2,1) * t;
    plot(line_x, line_y, 'b');
end
    
    
    
    
    
  
    