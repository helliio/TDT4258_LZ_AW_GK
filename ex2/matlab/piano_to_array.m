%Fs = 44100;
[y,Fs] = audioread('piano.mp3');
y = y(:, 1); % Make signal mono

y = y(y ~= 0); % Remove all zeros
y = y(1:8:length(y)/5); % decrese sampling frequency and reverberation
y = round((y + 1) .* 2^11);
y = y(y ~= 2048); % 0x800 repeats itself a lot in the beginning


header_name = fopen('piano_sound.h','w');

fprintf(header_name, 'int lenght_of_piano_sound = %d\n', length(y));
fprintf(header_name, 'int piano_sound[] = \n');
fprintf(header_name, '{');
for i = 1:4:length(y)-3
   fprintf(header_name, '    0x%03x, ', y(i)); 
   fprintf(header_name, '    0x%03x, ', y(i+1)); 
   fprintf(header_name, '    0x%03x, ', y(i+2)); 
   fprintf(header_name, '    0x%03x, \n', y(i+3)); 
end
fprintf(header_name, '};');

length(y)

max(y)

min(y)
