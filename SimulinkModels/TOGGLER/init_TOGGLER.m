function init_TOGGLER(params_filename)%this is the initialization file for the TOGGLER Simulink model, here you can specify constants and variables necessary for running and compiling your model 

load(params_filename)
% Variable definition


%% Variable definition


% Control Checks Parameters
MovAvWS = [30];                 % Moving Average In Seconds for Hub Height WindSpeed
MovAvWDir = [30];               % Moving Average In Seconds for Hub Height WindDirection
MovAvWMisalignment = [30];      % Moving Average In Seconds for Nacelle Wind Vane Misalignment

% Toggler Settings

InflowChecks_WaitTime  =  100;      % Duration of hysteresis block on inflow check. This is used to prevent rapid switching of WFC activation [s]
TogglingSeconds        = 3 * 60 ;  % Duration of toggling for each strategy [seconds]

Greedy_Status   = logical(true);  % This deactivates toggling with greedy
WFC_1_Status    = logical(true);  % This deactivates toggling with strategy 1
WFC_2_Status    = logical(true);  % This deactivates toggling with strategy 2
WFC_3_Status    = logical(true);  % This deactivates toggling with strategy 3

%
CTRL.MovAvWS   = round(MovAvWS*1/sample_time);
CTRL.MovAvWDir = round(MovAvWDir*1/sample_time);
CTRL.MovAvWMisalignment = round(MovAvWMisalignment*1/sample_time);

CTRL.TogglingSamples = round(1/sample_time.*TogglingSeconds);
CTRL.InflowChecks_WaitTime  = InflowChecks_WaitTime;

% Time Management (only if ActiveFlag is on)
CTRL.AutomTimeMGMT.ActivFlag = 0;    % Turn on or off time management
CTRL.AutomTimeMGMT.TriggerTime = 10; % [Hrs] deviations of one strategy from the average that would trigger Time Redistribution
CTRL.AutomTimeMGMT.ReductionFactor = 10; %[-] reduction factor for once a strategy has exceeded the limit

% Saturation Block
CTRL.SatBlock.WFC_OffsetRange = [-20 20];  % limit in degrees of offset

% Check input and startup
StartupTimeSamples = 30; % seconds before providing outputs, startup time
MovAvErrorCheck    = 10; % moving average window for the check on the inputs [seconds]
CTRL.InputCheck.StartupTimeSamples = round(1/sample_time.*StartupTimeSamples);
CTRL.InputCheck.MovAvErrorCheck = round(1/sample_time.*MovAvErrorCheck);

% Turbine Operational Parameters
%WT3
CTRL.WT3Par.PowProdStatus = 10;  % this should be replaced with the power production status of the turbine

% Create Model Struct (use this section to control on which sector to provide which offset)
CTRLSector.SectorLabel = [1;2];   % label of control sectors
CTRLSector.WakeSteering_WSRange = [4 11;   % wind speed range for wfc in each sectors [m/s]
    4 11];

CTRLSector.WakeSteering_WDirRange = [191 259;   % wind direction range for wfc in each sectors [deg]
    268 20];

CTRLSector.NacOrientationIsOK = [180 20    % nacelle orientation range for wfc in each sectors [deg] (necessary to prevent waked met mast signals to be used as a reference)
    180 20];
CTRLSector.MisalignmentLimit = [25; 25];   % wind turbine misalignment range for wfc in each sectors [deg]

CTRLSector.Sect1_WFCStrategiesLabel = [1 2 3];
CTRLSector.Sect2_WFCStrategiesLabel = [4];

% Perform checks on input. Check that WDirRange sector are exclusive
nStrat = length(CTRLSector.SectorLabel);
if size(CTRLSector.SectorLabel,1)~= nStrat || size(CTRLSector.WakeSteering_WDirRange,1)~= nStrat ...
        || size(CTRLSector.WakeSteering_WSRange,1)~= nStrat || size(CTRLSector.NacOrientationIsOK,1)~= nStrat ||...
        size(CTRLSector.MisalignmentLimit,1) ~= nStrat || sum(cell2mat(cellfun(@(x) contains(x,'WFCStrategies'),fieldnames(CTRLSector),'UniformOutput',false))) ~= nStrat
    error('Error: WFC Sector parameters not properly defined. Please check inputs.')
end

if size(CTRLSector.SectorLabel,2)~= 1 || size(CTRLSector.WakeSteering_WDirRange,2)~= 2 ...
        || size(CTRLSector.WakeSteering_WSRange,2)~= 2 || size(CTRLSector.NacOrientationIsOK,2)~= 2 ||...
        size(CTRLSector.MisalignmentLimit,2) ~= 1
    error('Error: WFC Sector parameters not properly defined. Please check input ranges.')
end


% Check that the sectors do not overlap
WDSC = CTRLSector.WakeSteering_WDirRange;
RefV = [0 : 0.5 : 360];

FF1 = [];
FF2 = [];
for i = 1 : length(RefV)
    FF1(i) = CheckIfWithinSectorAngle(WDSC(1,1), WDSC(1,2), RefV(i));
    FF2(i) = CheckIfWithinSectorAngle(WDSC(2,1), WDSC(2,2), RefV(i));
end

if sum(FF1 & FF2)> 0
    error('Sector Wind Direction ranges are overlapping. Please fix it.')
end

% Create Estimation Data Bus for Simulink Model
CTRLSector_BusInfo = Simulink.Bus.createObject(CTRLSector);
CTRLSector_Bus = evalin('base', CTRLSector_BusInfo.busName); % buses should be defined in Base workspace

%% Sect 2: assignments. Here all the defined variables that are useful for running the model are assigned to the parameter file
save(params_filename,'Greedy_Status','-append')
save(params_filename,'WFC_1_Status','-append')
save(params_filename,'WFC_2_Status','-append')
save(params_filename,'WFC_3_Status','-append')
save(params_filename,'CTRL','-append')
save(params_filename,'CTRLSector','-append')
save(params_filename,'CTRLSector_Bus','-append')

end 
