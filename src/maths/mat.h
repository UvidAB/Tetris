#pragma once
#include <array>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <math.h>
#include<cmath>
#include <math.h>
#include "vec.h"


namespace engine {namespace math {

		template<typename T, size_t Rows, size_t Cols>
		class Mat
		{
		public:
			Mat() { _data.fill(0); }

			Mat(std::array<T, Rows*Cols> data) {
				_data = data;
			}

			Mat<T, Rows, Cols> operator*(Mat<T, Rows, Cols>& other) {
				//static_assert (); 
				int n = 0;
				std::array<T, Rows* Cols> tmp;
				tmp.fill(0);
				

				for (int i = 0; i < Rows * Cols; i++) {
					for (int mCols = 0; mCols < Cols; mCols++) {
						
						tmp[i] += _data[((Rows * mCols) + (i % Rows))] * other[(mCols + (n * Rows))];

					}
					if ((i+1) % Rows == 0) {
						n += 1;
					}
				}

				return Mat<T, Rows, Cols>(tmp);
			}

			template<typename T, int N>
			Mat<T, Rows, Cols> operator*(Vec<T, N> vec) {
				int counter;
				std::array<T, Rows*Cols> tmp;
				static_assert(N  >= Cols);

				for (int i = 0; i < Rows; i++) {
					counter = 0;
					for (int j = 0; j < Cols; j++) {
						tmp[i] += _data[i+counter] * vec[j];
						counter += Cols;
					}
				}
				return Mat<T, Rows, Cols>(tmp);
			}

			T& operator()(int i, int j) {
				return _data[i + j * Rows];
			}

			T& operator[](int idx) {
				return _data[idx];
			}

			template<typename T, size_t Length>
			void translation(Vec<T, Length> vec) {
				int n = Rows * (Cols - 1);
				for (int i = 0; i < Length; i++) {

					_data[n + i] += vec[i];
				}
				
			}

		protected:
			std::array<T, Rows* Cols> _data;
		};
		typedef Mat<float, 2, 2> Mat2f;
		class Mat4f : public Mat<float, 4, 4>
		{
		public:
			Mat4f() : Mat<float, 4, 4>() {};
			Mat4f(std::array <float, 16 > data) : Mat<float, 4, 4>(data) {};
			Mat4f(Vec3f translation, Vec3f scale) {
				//translation
				std::array<float, 4 * 4> tMat;
				tMat.fill(0);
				
				for (int i = 0; i < 4; i++) {
					tMat[i*5] = 1.0f;

					if (i != 3) {
						tMat[i + 12] = translation[i];
					}
				}
				//scale
				for (int i = 0; i < 3; i++) {
					if (scale[i] != 0){
						tMat[i * 5] = scale[i];
					}
				}
				
				_data = tMat;

			}
			Mat4f(Vec3f translation) {
				//translation
				std::array<float, 4 * 4> tMat;
				tMat.fill(0);

				for (int i = 0; i < 4; i++) {
					tMat[i * 5] = 1.0f;

					if (i != 3) {
						tMat[i + 12] = translation[i];
					}
				}
				_data = tMat;
			}
			


			Mat4f(float theta, Vec3f rotation) {
			

				//Rotation
				std::array<float, 4 * 4> rMat;

				float Rxy = rotation.y * rotation.x;
				float Rzy = rotation.y * rotation.z;
				float Rzx = rotation.x * rotation.z;

				float pheta = (theta / 180) * 3.14159;
				rMat = {cos(pheta)+(rotation.x* rotation.x )*(1- cos(pheta)), Rxy *(1 - cos(pheta)) + rotation.z*(sin(pheta)) , Rzx*(1-cos(pheta)) - rotation.y*sin(pheta), 0,
				       Rxy*(1-cos(pheta)) - rotation.z*sin(pheta), cos(pheta) + (rotation.y * rotation.y)*(1-cos(pheta)), Rzy*(1-cos(pheta)) + rotation.x*sin(pheta), 0, 
					   Rzx* (1 - cos(pheta)) + rotation.y * sin(pheta), Rzy* (1 - cos(pheta)) - rotation.x * sin(pheta), cos(pheta) + (rotation.z * rotation.z)* (1 - cos(pheta)), 0,
						0,0,0,1	};

				_data = rMat;

			}

			Mat4f(const Mat<float, 4, 4>& base) : Mat<float, 4, 4>(base)
			{
			}


			float* to_glfloat() {
				return _data.data();
			}

			glm::mat4 to_glm() {
				return glm::make_mat4(_data.data());
			}
			void rotation(float pheta, Vec3f& rotation) {

			}
		private:
			


		};
		//typedef Mat<float, 4, 4> Mat4f;
		
}; // namespace math
} // namespace engine