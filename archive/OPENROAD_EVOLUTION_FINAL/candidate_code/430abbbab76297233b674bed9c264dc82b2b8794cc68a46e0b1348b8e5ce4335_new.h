// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.85417475;
  double density_weight = 0.16869275;
  double prefix_weight = 0.38862815;
  double neighborhood_weight = 0.12033202;
  double late_weight = 0.21111487;
  double critical_weight = 0.27408901;
  unsigned budget = 6;
  unsigned neighborhood = 16;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
