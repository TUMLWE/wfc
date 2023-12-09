function init_INFLW_1(params_filename)%this is the initialization file for the INFLW_1 Simulink model, here you can specify constants and variables necessary for running and compiling your model 

load(params_filename)
% Variable definition

%% Variable definition for INFLW block

MovAvWS =   [30];     % Moving Average In Seconds for Hub Height WindSpeed
MovAvWDir = [100];    % Moving Average In Seconds for Hub Height Wind Direction
MovAvTI =   [600];    % Moving Average In Seconds for Hub Height TI

ErrorChecks_WaitTime = 100; % Waiting time before switching error flag on single input [s]
MovAvErrorCheck      = 60;  % Checks for errors are performed on this time window of the signal [s]
StartupTime          = 200; %seconds,  Before this time, the application will flag error state

ParInflow.MovAvWS   = round(MovAvWS*1/sample_time);
ParInflow.MovAvWDir = round(MovAvWDir*1/sample_time);
ParInflow.MovAvTI   = round(MovAvTI*1/sample_time);
ParInflow.ErrorChecks_WaitTime = ErrorChecks_WaitTime;
ParInflow.MovAvErrorCheck      = round(MovAvErrorCheck*1/sample_time);
ParInflow.StartupTime          = round(StartupTime*1/sample_time);

% Sect 2: assignments. Here all the defined variables that are useful for running the model are assigned to the parameter file
save(params_filename,'ParInflow','-append')

end 
