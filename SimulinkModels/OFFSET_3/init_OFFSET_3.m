function init_OFFSET_3(params_filename)%this is the initialization file for the OFFSET_3 Simulink model, here you can specify constants and variables necessary for running and compiling your model 

load(params_filename)
% Variable definition

% This is only needed if some of parameters should be changed.
% Default values (already set up in Simulink):

% Explanation: The yaw offset is chosen from the vector possible_offsets
% (in degrees) and held for waiting_time (in seconds, not corrected for 
% inaccurate clock frequency)

possible_offsets = [0 15 0 -15];
waiting_time = 32.5*60;  

open_system('OFFSET_3')
set_param('OFFSET_3/possible_offsets/','Value',mat2str(possible_offsets))
set_param('OFFSET_3/Nmax/','Value',num2str(waiting_time/sample_time))
set_param('OFFSET_3/Unit Delay','SampleTime',num2str(sample_time))
set_param('OFFSET_3/Unit Delay1','SampleTime',num2str(sample_time))
set_param('OFFSET_3','FixedStep',num2str(sample_time))
close_system('OFFSET_3')

end 
