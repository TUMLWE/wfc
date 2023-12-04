function init_OFFSET_1(params_filename)%this is the initialization file for the OFFSET_1 Simulink model, here you can specify constants and variables necessary for running and compiling your model 

load(params_filename)
% Variable definition

load('LUT_SAMPLE_wd_ws_TI_shear.mat') % load sample LUT

% LUT entries
LUTOFFSET.WindSpeed = double(wind_speeds);
LUTOFFSET.WindDir = double(wind_directions);
LUTOFFSET.TurbInt = double(TIs);
LUTOFFSET.Shear   = double(shears);

LUTOFFSET.Offset = schedule;

% Sect 2: assignments. Here all the defined variables that are useful for running the model are assigned to the parameter file
save(params_filename,'LUTOFFSET','-append')

end 
