#ifndef HEXAPOD_DART_SIMU_HPP
#define HEXAPOD_DART_SIMU_HPP

#include <dart/dart.h>
#include <Eigen/Core>
#include <hexapod_dart/hexapod.hpp>
#include <hexapod_dart/hexapod_control.hpp>

#ifdef GRAPHIC
#include <osgDart/osgDart.h>
#endif

namespace hexapod_dart {

    class HexapodDARTSimu {
    public:
        using robot_t = std::shared_ptr<Hexapod>;

        HexapodDARTSimu(const std::vector<double>& ctrl, robot_t robot);

        ~HexapodDARTSimu();

        void run(double duration = 5.0, bool continuous = false, bool chain = false);

        robot_t robot();

        double covered_distance();

        std::vector<double> duty_cycle();

        double energy();
        double arrival_angle();
        Eigen::Vector3d final_pos();
        Eigen::Vector3d final_rot();

        double step();
        void set_step(double step);

        HexapodControl& controller();

        const std::vector<Eigen::Vector3d>& pos_traj();
        const std::vector<double>& rot_traj();

        const std::vector<double>& contact(int i);

    protected:
        bool _stabilize_robot(bool update_ctrl = false);

        void _add_floor();

        void _check_duty_cycle();

        std::vector<Eigen::Vector3d> _behavior_traj;
        std::vector<double> _rotation_traj;
        std::vector<double> _behavior_contact_0;
        std::vector<double> _behavior_contact_1;
        std::vector<double> _behavior_contact_2;
        std::vector<double> _behavior_contact_3;
        std::vector<double> _behavior_contact_4;
        std::vector<double> _behavior_contact_5;
        robot_t _robot;
        Eigen::Vector3d _final_pos;
        Eigen::Vector3d _final_rot;
        double _arrival_angle;
        double _covered_distance;
        double _energy;
        dart::simulation::WorldPtr _world;
        HexapodControl _controller;
        int _old_index;
#ifdef GRAPHIC
        osg::ref_ptr<osgDart::WorldNode> _osg_world_node;
        osgDart::Viewer _osg_viewer;
#endif
    };
}

#endif