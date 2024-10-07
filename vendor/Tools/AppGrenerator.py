import io
import os as os

from shutil import copytree
import re

from pathlib import Path

app_name = ""
choice = ""


def getAppName():
    global app_name
    app_name = input("app_name:")
    app_name = app_name.lower()


def checkAppName():
    if app_name == "":
        return False
    if not re.match("[a-zA-Z_]+$", app_name):
        return False
    if app_name == "template":
        return False
    return True


def createApp():
    global app_name, choice
    path = ""
    old_substring = r"\vendor"
    new_substring_s = r"\SysApp"
    new_substring_u = r"\UserApp"
    path = os.path.abspath(os.path.join(os.path.dirname(__file__), ".."))
    template_app_path = path.replace(old_substring, new_substring_s)
    # print("base path:{}\n".format(path))
    if choice == "S":
        path = path.replace(old_substring, new_substring_s)
    elif choice == "U":
        path = path.replace(old_substring, new_substring_u)
    # print("base path:{}\n".format(path))
    # 获取文件名
    folder_name = path + r"\app_" + app_name
    source_file_name = folder_name + r"\app_" + app_name + ".cpp"
    header_file_name = folder_name + r"\app_" + app_name + ".h"

    ui_folder = folder_name + r"\ui"
    source_ui_file_name = ui_folder + r"\app_" + app_name + "_ui" + ".cpp"
    header_ui_file_name = ui_folder + r"\app_" + app_name + "_ui" + ".h"

    asserts_folder = folder_name + r"\assets"
    # print("fold:{}\n".format(folder_name))
    # print("ui_fold:{}\n".format(ui_folder))
    # print("assets_fold:{}\n".format(asserts_folder))
    # print("file names:\n - {}\n - {}\n".format(source_file_name, header_file_name))

    # 创建文件夹

    os.makedirs(folder_name, exist_ok=True)
    os.makedirs(ui_folder, exist_ok=True)
    os.makedirs(asserts_folder, exist_ok=True)
    # 创建文件
    source_file = open(source_file_name, mode='x')
    header_file = open(header_file_name, mode='x')
    source_file_ui = open(source_ui_file_name, mode='x')
    header_file_ui = open(header_ui_file_name, mode='x')
    # print("template_path:{}\n".format(template_app_path))
    # # 读取模板内容
    content_source_file = open(template_app_path + "/app_template/app_template.cpp", mode='r').read()
    content_header_file = open(template_app_path + "/app_template/app_template.h", mode='r').read()
    content_source_file_ui = open(template_app_path + "/app_template/ui/app_template_ui.cpp", mode='r').read()
    # content_header_file_ui = open(template_app_path + "/app_template/ui/app_template_ui.h", mode='r').read()

    content_header_file_ui = io.open(template_app_path + "/app_template/ui/app_template_ui.h", mode='r',
                                     encoding='utf-8').read()

    # 替换应用程序类名
    app_class_name = app_name.capitalize().lower()
    print("app class name: {}".format("app " + app_class_name))
    # content_source_file = content_source_file.replace("template", app_class_name)
    # content_header_file = content_header_file.replace("template", app_class_name)
    # content_source_file_ui = content_source_file_ui.replace("template", app_class_name)
    # content_header_file_ui = content_header_file_ui.replace("template", app_class_name)
    #
    # # 替换文件名
    content_source_file = content_source_file.replace("app_template", "app_" + app_name)
    content_header_file = content_header_file.replace("app_template", "app_" + app_name)
    content_header_file = content_header_file.replace("APP_TEMPLATE", "APP_" + app_name.upper())
    content_source_file_ui = content_source_file_ui.replace("app_template", "app_" + app_class_name)
    content_header_file_ui = content_header_file_ui.replace("app_template", "app_" + app_class_name)
    content_header_file_ui = content_header_file_ui.replace("APP_TEMPLATE", "APP_" + app_name.upper())

    # 写入文件
    source_file.write(content_source_file)
    header_file.write(content_header_file)
    source_file_ui.write(content_source_file_ui)
    header_file_ui.write(content_header_file_ui)

    # 关闭文件
    source_file.close()
    header_file.close()
    source_file_ui.close()
    header_file_ui.close()


def installApp():
    global app_name
    old_substring = r"\vendor"
    new_substring_s = r"\AppUI\AppInstall\AppInstall.hpp"
    print("install app {}".format(app_name))

    # 获取基础路径
    base_path = os.path.abspath(os.path.join(os.path.dirname(__file__), ".."))

    # 替换路径中的子字符串
    path = base_path.replace(old_substring, new_substring_s)
    # print("path:{}\n".format(path))

    # 检查路径是否存在
    if not os.path.exists(path):
        print("Path does not exist: {}".format(path))
        return

    # 读取 app 安装回调文件
    with open(path, mode='r') as app_install_cb_file:
        content_app_install_cb_file = app_install_cb_file.read()

    header_include_tag = "/* Header files locator(Don't remove) */"
    app_install_tag = "/* Install app locator(Don't remove) */"

    # 根据选择替换头文件包含位置
    if choice == 'S':
        content_app_install_cb_file = content_app_install_cb_file.replace(
            header_include_tag,
            "#include \"SysApp/app_{}/app_{}.h\"\n{}".format(app_name, app_name.lower(), header_include_tag)
        )
    elif choice == 'U':
        content_app_install_cb_file = content_app_install_cb_file.replace(
            header_include_tag,
            "#include \"UserApp/app_{}/app_{}.h\"\n{}".format(app_name, app_name.lower(), header_include_tag)
        )

    # 替换应用安装标记
    content_app_install_cb_file = content_app_install_cb_file.replace(
        app_install_tag,
        ' auto {}= chipArch->installApp(new app_{}_packer);\n\tif (!{}) fmt::newline_info("error {{}}",{});\n\t{}'.
        format(
            app_name.capitalize().lower(),
            app_name.capitalize().lower(),
            app_name.capitalize().lower(),
            app_name.capitalize().lower(),
            app_install_tag)
    )

    # 写回修改后的内容
    with open(path, mode='w') as app_install_cb_file:
        app_install_cb_file.write(content_app_install_cb_file)


if __name__ == "__main__":
    print("ChipArch app generator >.<")
    print("Do not enter the following characters:_-#@%^&*")
    print("choice S or U 'S' mean system application 'U' mean user application")

    while True:
        choice = input("choice: ")
        if choice == "S" or choice == "U":
            break
        else:
            print("Invalid selection. Please choose 'S' or 'U'.")

    print("now choice is {}".format(choice))

    while True:
        getAppName()
        if checkAppName():
            break
        else:
            print("bad name, try again")

    print("get app name: {}\n".format(app_name))

    createApp()
    installApp()

    print("\ndone")
