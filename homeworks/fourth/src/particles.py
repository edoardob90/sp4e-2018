#!/usr/bin/env python3
import sys, os
import argparse
import numpy as np

# Pybind library
from pypart import MaterialPointsFactory, ParticlesFactoryInterface
from pypart import PingPongBallsFactory, PlanetsFactory
from pypart import CsvWriter
from pypart import ComputeTemperature

def generate_input(args):
    # Create the coordinate grid of particles
    x = np.linspace(args.x[0], args.x[1], num=args.shape[0],
            endpoint=True)
    y = np.linspace(args.y[0], args.y[1], num=args.shape[1],
            endpoint=True)

    xx, yy = np.meshgrid(x, y)
    zz = np.zeros((args.shape[0], args.shape[1]))

    # Particles are fixed on the grid, set forces and
    # velocities to zero
    vv = np.zeros((args.shape[0], args.shape[1]))
    ff = np.zeros((args.shape[0], args.shape[1]))

    # Set masses (used as mass density)
    mm = np.ones((args.shape[0], args.shape[1]))

    # Set initial temperature (1 everywhere,
    # corresponding to equilibrium)
    tt = np.ones((args.shape[0], args.shape[1]))

    # Set "boundary" points (don't update their
    # temperature during the simulation)
    bb = np.zeros((args.shape[0], args.shape[1]))

    # Uniform temperature distribution
    if args.type == 'uniform':
        hv = np.zeros((args.shape[0], args.shape[1]))
        #print(hv)

    # Delta function temperature distribution
    elif args.type == 'step':
        hv = np.zeros((args.shape[0], args.shape[1]))
        hv[:, int(0.25*args.shape[0])] = -1.0*args.shape[0]
        hv[:, int(0.75*args.shape[0])] = 1.0*args.shape[0]
        #print(hv)

    # Radial temperature distribution
    else:
        hv = np.zeros((args.shape[0], args.shape [1]))
        hv[np.where((xx**2 + yy**2) < args.r)] = 1.0
        bb[0, :] = 1
        bb[-1, :] = 1
        bb[:, 0] = 1
        bb[:, -1] = 1
        #print(hv)

    # Stack the columns for output
    out = np.column_stack((xx.flatten(order='C'),
            yy.flatten(order='C'),
            zz.flatten(order='C'),
            vv.flatten(order='C'),
            vv.flatten(order='C'),
            vv.flatten(order='C'),
            ff.flatten(order='C'),
            ff.flatten(order='C'),
            ff.flatten(order='C'),
            mm.flatten(order='C'),
            tt.flatten(order='C'),
            hv.flatten(order='C'),
            bb.flatten(order='C')))

    np.savetxt('input.csv', out, header='X Y Z VX VY VZ FX FY FZ M T HV B',
            delimiter=' ', fmt='%.3f %.3f %.3f %.3f %.3f %.3f %.3f %.3f %.3f %.3f %.3f %.3f %d')

def run_particles(args):
    nsteps = args.nsteps
    freq = args.freq
    fname = args.filename
    ptype = args.particle_type
    ts = args.timestep
    # First check if file exists
    if not os.path.isfile(fname):
        print("Filename {:s} doesn't exist! Run 'particles.py build' first.".format(fname), file=sys.stderr)
        sys.exit(-1)
    else:
        # Create 'dumps' dir
        dumps_dir = os.path.join(os.getcwd(),'dumps')
        try:
            os.mkdir(dumps_dir)
        except FileExistsError:
            print("Directory for dumps exists. Will overwrite dump files!")

        # Get an instance of the system of corresponding particles
        if ptype == "planet":
            PlanetsFactory.getInstance()
        elif ptype == "ping_pong":
            PingPongBallsFactory.getInstance()
        elif ptype == "material_point":
            MaterialPointsFactory.getInstance()
        else:
            print("Unknown particle type: ", ptype)
            sys.exit(-1)

        factory = ParticlesFactoryInterface.getInstance()

        def createComputes(self, timestep):
            compute_temp = ComputeTemperature()
            compute_temp.conductivity = 1
            compute_temp.L = 2
            compute_temp.capacity = 1
            compute_temp.density = 1

            # Read timestep from arg parser
            compute_temp.delta_t = ts
            self.system_evolution.addCompute(compute_temp)

        evol = factory.createSimulation(fname, ts, createComputes)

        # What is the purpose of these?
        #dumper = CsvWriter("init.csv")
        #dumper.write(evol.getSystem())

        evol.setNSteps(nsteps)
        evol.setDumpFreq(freq)
        evol.evolve()

# Parser(s)
parser = argparse.ArgumentParser(description="Python wrapper to particles code")
subparser = parser.add_subparsers(help="Available sub-commands")

# Build command
parser_build = subparser.add_parser('build', help="Generate the input file")
parser_build.add_argument('-shape', type=int, nargs=2, default=[12, 12],
        help='Number of particles in [x, y] directions')
parser_build.add_argument('-x', type=int, nargs=2, default=[-1, 1],
        help='Domain of x: [xmin, xmax]')
parser_build.add_argument('-y', type=int, nargs=2, default=[-1, 1],
        help='Domain of y: [ymin, ymax]')
parser_build.add_argument('-type', type=str, default='uniform',
        choices=['uniform', 'step', 'radial'],
        help='Type of initial heat distribution')
parser_build.add_argument('-r', type=float, default=1.0,
        help='Radius of radial heat distribution (ignored for other types)')
parser_build.set_defaults(func=generate_input)

# Run command
parser_run = subparser.add_parser('run', help="Run the particles code")
# Compulsory arguments
parser_run.add_argument('particle_type', type=str,
        choices=['planet', 'ping_pong', 'material_point'],
        help='Particle type')

# Optional arguments, with default values
parser_run.add_argument('-filename', type=str, default='input.csv',
        help='Input filename. Default: input.csv')
parser_run.add_argument('-nsteps', type=int, default=100,
        help='Total number of simulation steps. Default: 100')
parser_run.add_argument('-freq', type=int, default=1,
        help='Frequency for dumps. Default: every step')
parser_run.add_argument('-timestep', type=float, default=1.0,
        help='Simulation timestep. Default: 1.0')
parser_run.set_defaults(func=run_particles)

if len(sys.argv) == 1:
    parser.print_help(sys.stderr)
else:
    args = parser.parse_args()
    args.func(args)
