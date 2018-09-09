/*
 * Methods For Recording Images
 */
#ifndef IMAGE_TOOLS_HPP
#define IMAGE_TOOLS_HPP

#include "tools.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include <unordered_map>

namespace img_tools {
	
	// padrão
	static const std::string WORKSPACE = "Workspace";
	static const std::string WORKSPACE_IMGP = "/imgp";
	static const std::string WORKSPACE_OUT = "/output";
	static const std::string METHOD = "M0_";

	static const std::unordered_map<std::string, std::string> map_default = {
		{"ORIGINAL"  , "/original"},
		{"GRAYSCALE" , "/grayscale"},
		{"BINARY"    , "/binary"},
		{"BINARY_INV", "/binary_inv"}
	};	

	static const std::unordered_map<std::string, std::string>
	map_extension = {
		{"PNG", "png"}, {"JPG", "jpg"}, {"JPEG", "jpeg"},
	};

	// configuração inicial - variáveis públicas
	std::vector<std::string> info;
	std::string directory, filename, extension, name;
	std::string workspace(WORKSPACE);
	std::string method_name(METHOD);
	std::string imgp_path, path_temp;

	void error(int line, const std::string& msg)
	{
		throw std::domain_error("[Line: " + std::to_string(line) + "]: " + msg);
	}

	void validate (const std::string& file_image)
	{
		if (!tools::check_extension(tools::upper(extension), map_extension))
			error(__LINE__, "img_tools::validate, invalid file_image in.\n");		
	}

	void info_path(const std::string& file_image)
	{
		try {
			tools::split_path(file_image, info);
		}
		catch(const std::exception& e) {
			error(__LINE__, "img_tools::info_path\n");
		}
		
		directory = info[0];
		filename = info[1];
		extension = info[2];
		name = info[3];
	}	

	bool exist_workspace(const std::string& new_workspace)
	{
		if (!tools::exist_path(new_workspace)) {
			std::cout << "Workspace don't exist!\n";
			return false;
		}
		return true;
	}

	void create_workspace(const std::string& new_workspace = workspace, 
		const std::unordered_map<std::string, std::string>&
		map_work = map_default)
	{
		try {
			if (exist_workspace(new_workspace)) return;

			if (new_workspace.empty()) {
				std::cout << "string workspace empty!\n";
				return;
			}

			if (map_work.empty()) {
				std::cout << "map currently empty!\n";
				return;
			}

			tools::create_directory(new_workspace);
			tools::create_directory(new_workspace + WORKSPACE_IMGP);
			tools::create_directory(new_workspace + WORKSPACE_OUT);

			for (auto it : map_work) {
				tools::create_directory(new_workspace + WORKSPACE_OUT
					+ std::string(it.second));
			}
		}
		catch(const std::exception& e) {
			error(__LINE__, "img_tools::create_workspace");
		}
	}

	void save_imgp(const std::string& file_image,
		const std::string& new_workspace = workspace,
		const std::unordered_map<std::string, std::string>&
		map_work = map_default)
	{
		try {
			if (!exist_workspace(new_workspace))
				create_workspace(new_workspace);

			info_path(file_image);
			validate(file_image);			
 
			imgp_path = new_workspace + WORKSPACE_IMGP + "/" + method_name
				+ name + ".imgp";
			std::cout << "save .imgp: " << imgp_path;
			tools::save_new_file(imgp_path);

			for (auto it: map_work) {
				path_temp = std::string(it.first) + ":" + new_workspace
					+ WORKSPACE_OUT + std::string(it.second) + "/"
					+ filename + "\n";
				tools::write(path_temp, imgp_path);
			}
			tools::write("WORKSPACE:" + new_workspace + "\n", imgp_path);

			std::cout << " ... ok" << '\n';
		}
		catch(const std::exception& e) {
			error(__LINE__, "img_tools::create_imgp");
		}		
	}

	std::vector<std::vector<std::string> > load_imgp(const std::string& file_imgp)
	{
		std::vector<std::string> lines, word;
		std::vector<std::vector<std::string> > result {{"EMPTY"}};
		try {
			tools::load(file_imgp, lines);
			for (std::string line : lines) {
				tools::split(line, word, ':');
				result.push_back(word);
			}
		}
		catch(const std::exception& e) {
			error(__LINE__, "img_tools::load_imgp");
		}
		return result;
	}
};

#endif // IMAGE_TOOLS_HPP