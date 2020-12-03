#pragma once

namespace engine {
namespace math {

	template<typename T, size_t Length>
	class Vec
	{
	public:
		Vec() {};
		Vec(std::array<T, Length> data) {
			_data = data;
		}
		Vec(float *data) {
			_data = data;
		}

		Vec<T, Length> operator+(Vec<T, Length>& other) {
			std::array<T, Length> tmp;
			for (int i = 0; i < Length; i++) {
				tmp[i] = _data[i] + other[i];
			}
			return Vec<T, Length>(tmp);
		}

		Vec<T, Length> operator-(Vec<T, Length>& other) {
			std::array<T, Length> tmp;
			for (int i = 0; i < Length; i++) {
				tmp[i] = _data[i] + other[i];
			}
			return Vec<T, Length>(tmp);
		}

		T& operator[](int idx) {
			return _data[idx];
		}

	protected:
		std::array<T, Length> _data;
	};

	typedef Vec<float, 4> Vec4f;
	typedef Vec<int, 3> Vec3i;




	class Vec3f : public Vec<float, 3> {
	public:
		Vec3f() : Vec<float, 3>(){}
		Vec3f(std::array <float, 3> data) : Vec <float, 3>(data) {}

		float x = _data[0];
		float y = _data[1];
		float z = _data[2];


	};

}; // namespace math
} // namespace engine