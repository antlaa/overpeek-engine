#pragma once

#include "vk_window.hpp"
#include "vk_instance.hpp"

#include <vulkan/vulkan.hpp>
#include <optional>



namespace oe::graphics {

	struct QueueFamilyIndices {
		std::optional<uint32_t> graphicsFamily;
		std::optional<uint32_t> presentFamily;

		bool isComplete() {
			return graphicsFamily.has_value() && presentFamily.has_value();
		}
	};

	class PhysicalDevice {
	public:
		vk::PhysicalDevice m_physical_device;
		vk::PhysicalDeviceProperties m_physical_device_properties;

		const VKInstance* m_instance;
		const vk::SurfaceKHR& m_surface;

	public:
		PhysicalDevice(const VKInstance* instance, const vk::SurfaceKHR& surface);
		~PhysicalDevice();

		QueueFamilyIndices findQueueFamilies() const;

	private:
		static QueueFamilyIndices findQueueFamilies(vk::PhysicalDevice device, const vk::SurfaceKHR& window);
		bool isDeviceSuitable(vk::PhysicalDevice device);
		int rateDeviceSuitability(vk::PhysicalDevice device);
		vk::PhysicalDevice bestPhysicalDevice(const std::vector<vk::PhysicalDevice>& devices);
		void pickPhysicalDevice();

	};

}