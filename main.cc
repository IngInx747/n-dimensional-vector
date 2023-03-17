#include "vector_n.hh"

////////////////////////////////////////////////////////////////
/// Main
////////////////////////////////////////////////////////////////

using Vec = VectorN<double, 4>;
using std::cout;
using std::endl;

int main()
{
    Vec a {-1,3.5}, b {2,2.5};
    cout << a + b << endl;
    cout << a - b << endl;
    cout << a * b << endl;
    cout << a / b << endl;
    cout << max(a,b) << endl;
    cout << min(a,b) << endl;
    cout << max(a) << " " << argmax(a) << endl;
    cout << max(b) << " " << argmax(b) << endl;
    cout << min(a) << " " << argmin(a) << endl;
    cout << min(b) << " " << argmin(b) << endl;
    cout << abs(a) << endl;
    cout << sum(a) << endl;
    cout << norm1(a) << endl;
    cout << norm2(a) << endl;
    cout << norm8(a) << endl;
    cout << norm(a, 1.) << endl;
    cout << norm(a, 2.) << endl;
    cout << norm(a, 3.) << endl;
    cout << norm(a, 4.) << endl;
    cout << norm(a, 8.) << endl;
    cout << norm(a, 16.) << endl;
    cout << dot(a,b) << endl;
    cout << exp(a) << endl;
    cout << log(exp(a)) << endl;
    cout << normalize(a) << endl;
    cout << make_vector<double, 6>(3.1416) << endl;
    a += b; cout << a << endl;
    return 0;
}
