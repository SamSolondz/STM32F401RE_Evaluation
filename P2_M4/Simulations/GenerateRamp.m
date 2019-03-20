%   Simulation of Ramp Generator
%   0 to 3V
%   1004Hz
N_SAMPLES = 1024;
amp_buffer = zeros(N_SAMPLES, 2);
time_stamp = 0;
count = 1;
i = 0;
   while count <= N_SAMPLES
           if i == 256
               i = 0;
           end
           amp_buffer(count, 1) = time_stamp;
           amp_buffer(count, 2) = i;
           i = i + 1;
           time_stamp = time_stamp + 1;
           count = count + 1;
           
   end
   amp_buffer(:,2) = amp_buffer(:,2) /255 * 3;
   amp_buffer(:,1) = amp_buffer(:,1)/255;
   xlswrite('output.xls', amp_buffer);
   plot(amp_buffer(:, 1), amp_buffer(:,2));
   xlabel("Time (s)");
   ylabel("Voltage (V)");