function RayProp_jch

c0 = 299792458; %Speed of light, m/s
%~ f = @nfirnmeas_SPICE; %Function handle for firn from SPICE Core
%~ f = @nfirnmeas1; %Function handle for firn measurement #1
%~ f = @nfirn;
f = @nfirn_sp;
%~ f = @nfirnmeas_MooresBay2;
zmax=0.0; %Maximum depth of the medium
zmin=-2700.0; %Minimum depth of the medium
z0 = -300.0; %Position of the emitter in z coordinate
x0 = 0.0; %Position of the emitter in x coordinate
reflection = 0; %Account for reflections?
dt = 1/c0; %time steps, 1 meter divided by speed of light in m/s
tend = 1000.0/c0; %end time, n time steps
the_angle = 30.0;

figure(1,'Position',[0,0,1200,240]);
linew = 3.0;
fon = "Courier";
fonts = 20.0;
linewc = 0.0;
linewc2 = 4.0;
hold on;
set(gca, "linewidth", linew, "fontname", fon,"fontsize",fonts);
xlabel('Distance (m)');
ylabel('Depth (m)');
title("Smooth Index of Refraction Model","fontname", fon,"fontsize",fonts);
z = z0;
x = x0;
alpha = the_angle/180.0*pi;
t = 0;
goon = 1;
tarray = [];
alpharray = [];
narray = [];
xarray = [];
zarray = [];
while goon
	tarray = [tarray; t];
	xarray = [xarray; x];
	zarray = [zarray; z];
	n = f(z);
	zold = z;
	xold =x;
	z = z + sin(alpha)*dt*c0/(n);
	x = x + cos(alpha)*dt*c0/(n);
	if(or(z>=0,z<=zmin) && reflection)
		alpha = -alpha;
		if(z>=0)
			z = 0;
		end
		if(z<=zmin)
			z=zmin;
		end
	end
	if(abs(z-zold)>1e-4)
		dndz = (f(z)-f(zold))/(z-zold);
	else
		dndz = (f(z)-f(z-1e-4))/(z-1e-4);
	end
	dcdz = -dndz*c0/(n*n);
	dalpha = -dt*cos(alpha)*dcdz;
	alpha = alpha+dalpha;
	alpharray = [alpharray; alpha];
	narray = [narray; n];
	t = t + dt;
	if (t>tend), goon = 0; end
end
xarray = [xarray; x];
zarray = [zarray; z];
plot (xarray,zarray,'-','LineWidth',1,'Color','b','Linestyle','-')

%The saved graph.
print -dpdf 'May10_plot1.pdf'
end

function y = nfirn(z)
y = 1.0 + 0.86*(1.0 - 0.638 * exp(z/34.7) );
end

function y = nfirn_sp(z)
y = 1.78-0.427*exp(z/71.0);
end

function y = nfirnmeas_SPICE(z)
data = load('/home/jordan/ANewHope/SPICE_data.dat');
vdepth = -data(:,1);
vrho = data(:,2);
if z<=0,
    itemp = find(z<=vdepth);
    if(length(itemp)>=length(vdepth))
		y = nfirn_sp(z);
	else
		idepth = itemp(end);
		rho = vrho(idepth) + (vrho(idepth+1) - vrho(idepth))/(vdepth(idepth+1) - vdepth(idepth))*(z - vdepth(idepth));
		rho=rho/1000.0; %scale to density of water
		y = 1 + 0.86*rho;
	end
else
    y = 1;
end
end

function y = nfirnmeas_MooresBay1(z)
data = load('/home/jordan/ANewHope/ARIANNA_BoreHole_1.dat');
vdepth = -data(:,1);
vrho = data(:,2);
if z<=0,
    itemp = find(z<=vdepth);
    if(length(itemp)>=length(vdepth))
		y = nfirn_sp(z);
	else
		idepth = itemp(end);
		rho = vrho(idepth) + (vrho(idepth+1) - vrho(idepth))/(vdepth(idepth+1) - vdepth(idepth))*(z - vdepth(idepth));
		rho=rho/1000.0; %scale to density of water
		y = 1 + 0.86*rho;
	end
else
    y = 1;
end
end

function y = nfirnmeas_MooresBay2(z)
data = load('/home/jordan/ANewHope/ARIANNA_BoreHole_2.dat');
vdepth = -data(:,1);
vrho = data(:,2);
if z<=0,
    itemp = find(z<=vdepth);
    if(length(itemp)>=length(vdepth))
		y = nfirn_sp(z);
	else
		idepth = itemp(end);
		rho = vrho(idepth) + (vrho(idepth+1) - vrho(idepth))/(vdepth(idepth+1) - vdepth(idepth))*(z - vdepth(idepth));
		rho=rho/1000.0; %scale to density of water
		y = 1 + 0.86*rho;
	end
else
    y = 1;
end
end
