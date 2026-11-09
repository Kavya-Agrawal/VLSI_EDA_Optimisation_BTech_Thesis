// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.86252617;
  double density_weight = 0.14628206;
  double prefix_weight = 0.34455591;
  double neighborhood_weight = 0.07346751;
  double late_weight = 0.14183170;
  double critical_weight = 0.46365877;
  unsigned budget = 33;
  unsigned neighborhood = 2;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
