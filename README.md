range

A lightweight, header-only, type-safe range and multi-dimensional spatial validation library for standard C (C99+).

Architecture & Design Goals

Unlike monolithic type headers or raw inline comparison macros, this library decouples boundary configurations from dynamic evaluation values. It avoids compiler-specific hacks (like GNU typeof or variable-shadowing macro extensions) by utilizing an explicit, type-parameterized composition layer.
• Explicit Type Parameterization: Prevents variable shadowing and eliminates sign/mismatch comparison faults at compile time.
• Separation of Concerns: The structure retains only the boundaries (minimum and maximum), leaving the coordinate data to be evaluated as a separate dynamic parameter.
• Zero Dependency & High Portability: Incorporates explicit type abstractions natively supported by <stddef.h>, <stdint.h>, and <sys/types.h>, making it ideally suited for bare-metal systems, custom drivers, and resource-constrained execution frames.

License Protection

This project is licensed under the GNU General Public License v3.0 (GPLv3).
Independent developers are completely free to share, modify, and integrate this header within their open-source projects. However, proprietary and commercial exploitation is strictly prohibited unless the target product's entire source code is also made public under the same copyleft license terms.

Technical Implementation


Code Layout

The master library is designed to sit directly inside your universal inclusions tree:
include/common/range.h

Core Interfaces


1D Scalar Ranges

c
RANGE_MACRO( type )
RANGE_ALIAS_MACRO( type, alias_name )
Use code with caution.
Generates custom-named boundary tracking structures (e.g., doubleRange, UInt16Range, Int32Range). Evaluation is executed using highly efficient mathematical macros:
• IN_RANGE( value, range )
• NOT_IN_RANGE( value, range )

Advanced Multi-Dimensional Spatial Composition (2D/3D)

Most open-source spatial boundaries fall into the trap of repeating loose primitive values inside their structure definitions (e.g., min_x, max_x, min_y, max_y). This library completely avoids that redundancy by composing higher-dimensional validation layers directly from existing scalar range types.
c
/* Compose bounding blocks directly from your existing type choices */
DEFINE_BOX_2D( x_range_type, y_range_type, name )
DEFINE_CUBE_3D( x_range_type, y_range_type, z_range_type, name )
Use code with caution.

Production Use Cases & Optimization


Drastic Function Argument Reduction

Passing raw variables across coordinates quickly leads to bloated function contracts that drain CPU registers and stack frames (requiring 6 parameters for 2D or up to 9 parameters for 3D validation checks).
By structuring both your bounding objects and coordinate metrics into unified blocks, you reduce function contracts dramatically down to just two efficient pointers:
c
#include "common/range.h"
#include <stdbool.h>

/* 1. Instantiate the specialized hybrid tracking layers */
/* Azimuth and Elevation use signed angles; Distance uses unsigned values */
DEFINE_CUBE_3D(Int16Range, Int16Range, UInt32Range, RadarWindow)

/* 2. Group spatial coordinates into a matching compact container */
typedef struct
{
    int16_t  azimuth;
    int16_t  elevation;
    uint32_t distance;
} RadarPoint3D;

/* 3. High-Efficiency Contract: Reduced from 9 arguments down to 2 pointers! */
bool is_target_in_window(const RadarWindowCube3D *window, const RadarPoint3D *target)
{
    return IN_CUBE_3D(target->azimuth, target->elevation, target->distance, *window);
}
Use code with caution.
Under -O2 compilation, the nested macro block expands cleanly into flat register comparisons and branch jumps with zero call-stack overhead, achieving complete data-type flexibility without wasting a single CPU cycle.

---

## Commercial Licensing & Enterprise Support

While this library is distributed under the open-source **GPLv3 license** for community integration, proprietary device manufacturers, enterprise software vendors, and closed-source commercial hardware teams can procure a **Commercial Proprietary License**.

Acquiring a commercial license completely waives the copyleft requirement, allowing your organization to integrate the stack-optimized, parameter-reducing math of this validation engine within your closed-source firmware assets without being legally forced to disclose or share your proprietary application source code.

### Commercial Procurement Tiers

*   **Startup / Per-Product License ($495 single-payment):** Grants perpetual usage rights to embed the library within one specified commercial product line. Includes 30 days of direct integration email support.
*   **Corporate Site License ($2,495/year subscription):** Unlimited usage across all internal fixtures, product lines, and development teams operating at a single designated facility or team site. Includes priority 48-hour email support.
*   **Enterprise Buyout License ($7,500 single-payment):** Perpetual, worldwide, royalty-free usage across any product developed or manufactured by the organization, including distribution and sub-licensing rights for tier-1 supply networks. Includes 1 year of direct engineering architecture alignment reviews.

For enterprise procurement processing, bulk licensing verification, custom vendor registration, or corporate invoice handling, please contact: **dandeluca@att.net**

