import os
from launch import LaunchDescription
from launch.actions import IncludeLaunchDescription, DeclareLaunchArgument
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch.substitutions import LaunchConfiguration, Command, PythonExpression
from launch_ros.actions import Node
from launch.conditions import IfCondition
from launch_ros.parameter_descriptions import ParameterValue
from ament_index_python.packages import get_package_share_path, get_package_share_directory

def generate_launch_description():
    urdf_path = os.path.join(get_package_share_path('explorer_bot'),
                             'urdf', 'my_robot.urdf.xacro')

    gazebo_world_path = os.path.join(get_package_share_path('simulation_environment'),
                             'worlds', 'train_world.world')

    rviz_config_path = os.path.join(get_package_share_path('simulation_environment'),
                             'rviz', 'urdf_config.rviz')

    robot_description = ParameterValue(Command(['xacro ', urdf_path]), value_type=str)

    use_sim_time = LaunchConfiguration('use_sim_time', default='true')

    robot_type = LaunchConfiguration('robot_type')

    gazebo = IncludeLaunchDescription(
        PythonLaunchDescriptionSource([os.path.join(
            get_package_share_directory('gazebo_ros'), 'launch', 'gazebo.launch.py')]),
        launch_arguments={'world': gazebo_world_path}.items(),
    )

    robot_state_publisher = Node(
        package='robot_state_publisher',
        executable='robot_state_publisher',
        parameters=[{'robot_description': robot_description}],
        output='screen'
    )

    rviz2_node = Node(
        package="rviz2",
        executable="rviz2",
        arguments=['-d', rviz_config_path],
        parameters=[{'use_sim_time': use_sim_time}]
    )

    spawn_entity_A = Node(
            package='gazebo_ros',
            executable='spawn_entity.py',
            arguments=[
                '-topic', 'robot_description',
                '-entity', 'my_bot'
            ],
            output='screen',
            condition=IfCondition(PythonExpression(["'", LaunchConfiguration('robot_type'), "' == 'A'"]))
        )

    spawn_entity_B = Node(
        package='gazebo_ros',
        executable='spawn_entity.py',
        arguments=[
            '-topic', 'robot_description',
            '-entity', 'my_bot',
            '-x', '-3', '-y', '-3'
        ],
        output='screen',
        condition=IfCondition(PythonExpression(["'", LaunchConfiguration('robot_type'), "' == 'B'"]))
    )

    spawn_entity_C = Node(
        package='gazebo_ros',
        executable='spawn_entity.py',
        arguments=[
            '-topic', 'robot_description',
            '-entity', 'my_bot',
            '-x', '3', '-y', '1'
        ],
        output='screen',
        condition=IfCondition(PythonExpression(["'", LaunchConfiguration('robot_type'), "' == 'C'"]))
    )    

    lidar_node = Node(
        package='simulation_environment',
        executable='lidar_node.py',
        name='lidar_node',
        output='screen',
    )

    test_auto_drive_node = Node(
        package='simulation_environment',
        executable='test_auto_drive_node.py',
        name='test_auto_drive_node',
        output='screen',
        parameters=[{'robot_type': robot_type}]
    )

    return LaunchDescription([
        DeclareLaunchArgument(
            'robot_type',
            default_value='C',
            description='Type of robot to train (A, B or C)'
        ),
        robot_state_publisher,
        gazebo,
        spawn_entity_A,
        spawn_entity_B,
        spawn_entity_C,
        rviz2_node,
        lidar_node,
        test_auto_drive_node
    ])
