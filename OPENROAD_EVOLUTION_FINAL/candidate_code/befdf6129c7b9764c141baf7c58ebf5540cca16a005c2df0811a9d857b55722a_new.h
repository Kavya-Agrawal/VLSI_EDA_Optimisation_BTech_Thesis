// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.07362427;
  double density_weight = 0.22322112;
  double prefix_weight = 0.23079501;
  double neighborhood_weight = 0.07459676;
  double late_weight = 0.22150001;
  double critical_weight = 0.37704732;
  unsigned budget = 10;
  unsigned neighborhood = 16;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
