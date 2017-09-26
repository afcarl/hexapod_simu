#include <iostream>
#include <cstdlib>
#include <hexapod_dart/hexapod_dart_simu.hpp>

struct Params {
    static constexpr double radius() { return 0.01; }

    static Eigen::Vector3d head() { return Eigen::Vector3d(1, 1, 0.5); }

    static Eigen::Vector3d tail() { return Eigen::Vector3d(1, 0, 0.5); }

    static Eigen::Vector4d color() { return Eigen::Vector4d(1, 0, 0, 1); }

    static std::string skel_name() { return "floor"; }

    static std::string body_name() { return "BodyNode"; }
};

int main()
{
    std::vector<hexapod_dart::HexapodDamage> brk = {};
    // Examples of leg damages
    // hexapod_dart::HexapodDamage dmg;
    // dmg.type = "leg_shortening";
    // dmg.data = "2";
    // brk.push_back(dmg);
    // dmg.type = "leg_removal";
    // dmg.data = "2";
    // brk.push_back(dmg);
    // dmg.type = "blocked_joint";
    // dmg.data = "body_leg_1";
    // dmg.extra = new double(1.0);
    // brk.push_back(dmg);
    // dmg.type = "blocked_joint";
    // dmg.data = "leg_1_1_2";
    // dmg.extra = nullptr;
    // brk.push_back(dmg);
    // dmg.type = "blocked_joint";
    // dmg.data = "leg_1_2_3";
    // brk.push_back(dmg);

    auto global_robot = std::make_shared<hexapod_dart::Hexapod>(std::string(std::getenv("RESIBOTS_DIR")) + "/share/hexapod_models/URDF/pexod.urdf", brk);

    std::vector<double> ctrl;
    ctrl = {1, 0, 0.5, 0.5, 0.25, 0.5, 0.5, 0.25, 0.5, 1, 0.5, 0.5, 0.5, 0.75, 0.5, 0.5, 0.75, 0.5, 1, 0, 0.5, 0.5, 0.25, 0.5, 0.5, 0.25, 0.5, 1, 0, 0.5, 0.5, 0.75, 0.5, 0.5, 0.75, 0.5, 1, 0.5, 0.5, 0.5, 0.25, 0.5, 0.5, 0.25, 0.5, 1, 0, 0.5, 0.5, 0.75, 0.5, 0.5, 0.75, 0.5};

    using desc_t = boost::fusion::vector<hexapod_dart::descriptors::DutyCycle, hexapod_dart::descriptors::BodyOrientation>;
    using viz_t = boost::fusion::vector<hexapod_dart::visualizations::HeadingArrow, hexapod_dart::visualizations::PointingArrow<Params>>;
    hexapod_dart::HexapodDARTSimu<hexapod_dart::desc<desc_t>, hexapod_dart::viz<viz_t>> simu(ctrl, global_robot);
#ifdef GRAPHIC
    simu.fixed_camera(Eigen::Vector3d(0, 1, 5));
#endif
    Eigen::Vector6d p;
    p << 0, 0, 0, 1, -1, 0.15;
    simu.add_box(p, Eigen::Vector3d(0.3, 0.3, 0.3));
    p << 0, 0, 0, 1, 1, 0;
    simu.add_ellipsoid(p, Eigen::Vector3d(0.3, 0.3, 0.3), "fixed");

    simu.run(5);
    std::cout << simu.covered_distance() << " " << simu.arrival_angle() << std::endl;
    std::cout << simu.energy() << std::endl;
    std::vector<double> v;
    simu.get_descriptor<hexapod_dart::descriptors::DutyCycle>(v);
    for (size_t i = 0; i < v.size(); i++) {
        std::cout << v[i] << " ";
    }
    std::cout << std::endl;
    std::vector<double> vv;
    simu.get_descriptor<hexapod_dart::descriptors::BodyOrientation>(vv);
    for (size_t i = 0; i < vv.size(); i++) {
        std::cout << vv[i] << " ";
    }
    std::cout << std::endl;

    global_robot.reset();
    return 0;
}
